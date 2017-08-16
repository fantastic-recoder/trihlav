/*
 * trihlavYubikoOptKeyPresenter.cpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/locale/message.hpp>
#include <boost/format.hpp>

#include "trihlavLib/trihlavButtonIface.hpp"
#include "trihlavLib/trihlavEditIface.hpp"
#include "trihlavLib/trihlavFactoryIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavMessageViewIface.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavSpinBoxIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyViewIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavSysUserListPresenter.hpp"

using namespace std;
using namespace boost;
using namespace boost::locale;
using boost::filesystem::path;

namespace trihlav {

void YubikoOtpKeyPresenter::initUi() {
	getView().setOkLabel(translate("Save"));
	getView().getEdtPrivateId().setValue("");
	getView().getEdtSecretKey().setValue("");
	getView().getEdtPublicId().setValue("");
	getView().getSbxPublicIdLen().setValue(6);
	getView().getSbxPublicIdLen().setMin(0);
	getView().getSbxPublicIdLen().setMax(6);
	getView().getSbxPublicIdLen().setStep(1);
	getView().sigDialogFinished.connect([this](const bool pAccepted) {
		accepted(pAccepted);
	});
	getView().getBtnGenPrivateId().pressedSig.connect([this]() {
		generatePrivateId();
	});
	getView().getBtnGenPublicId().pressedSig.connect([this]() {
		generatePublicId();
	});
	getView().getBtnGenSecretKey().pressedSig.connect([this]() {
		generateSecretKey();
	});
	getView().getBtnSelectSysUser().pressedSig.connect([this]() {
		selectSystemUser();
	});
}

void YubikoOtpKeyPresenter::selectSystemUser() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::selectSystemUser");
	getSysUserListPresenter().show();
}

void YubikoOtpKeyPresenter::systemUserSelected() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::systemUserSelected");
	std::string mySelectedUser{getSysUserListPresenter().getSelectedSysUser()};
	BOOST_LOG_TRIVIAL(debug)<<"selected "<<mySelectedUser;
	getView().getEdtSysUser().setValue(mySelectedUser);
}

YubikoOtpKeyPresenter::YubikoOtpKeyPresenter(FactoryIface& pFactory) :
		PresenterBase(pFactory), m_CurCfg(0) {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::YubikoOptKeyPresenter");
}

YubikoOtpKeyPresenter::~YubikoOtpKeyPresenter() {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::~YubikoOptKeyPresenter");
	delete m_CurCfg;
}

void YubikoOtpKeyPresenter::showCurrentConfig() {
	getView().getEdtDescription().setValue(getCurCfg().getDescription());
	getView().getEdtPrivateId().setValue(getCurCfg().getPrivateId());
	getView().getEdtPublicId().setValue(getCurCfg().getPublicId());
	getView().getEdtSecretKey().setValue(getCurCfg().getSecretKey());
	getView().show();
}

void YubikoOtpKeyPresenter::addKey() {
	delete m_CurCfg;
	m_CurCfg = 0;
	getCurCfg();
	m_Mode = Add;
	showCurrentConfig();
}

void YubikoOtpKeyPresenter::deleteKey(const YubikoOtpKeyConfig& pKeyCfg) {
	delete m_CurCfg;
	m_CurCfg = new YubikoOtpKeyConfig { pKeyCfg };
	m_Mode = Delete;
	if (getMessageView().ask(translate("Trihlav question"),
			translate(
					"Really delete key \"" + m_CurCfg->getDescription()
							+ "\"."))) {
		deleteKey();
		saved();
		m_Mode = None;
	}
}

void YubikoOtpKeyPresenter::editKey(const YubikoOtpKeyConfig& pKeyCfg) {
	delete m_CurCfg;
	m_CurCfg = new YubikoOtpKeyConfig { pKeyCfg };
	m_Mode = Edit;
	showCurrentConfig();
}

YubikoOtpKeyConfig& YubikoOtpKeyPresenter::getCurCfg() {
	if (!m_CurCfg) {
		m_CurCfg = new YubikoOtpKeyConfig(getFactory().getKeyManager());
	}
	return *m_CurCfg;
}

void YubikoOtpKeyPresenter::deleteKey() {
	if (m_CurCfg) {
		const path myFilename = getCurCfg().getFilename();
		if (exists(myFilename)) {
			getFactory().getKeyManager().prefixKeyFile(myFilename, "deleted");
		} else {
			BOOST_LOG_TRIVIAL(warning)<< "Filename " << myFilename
			<< " does not exist.";
		}
	} else {
		throwNoConfig();
	}
}

void YubikoOtpKeyPresenter::throwNoConfig() {
	const string myErrMsg =
			translate(
					"Internal error, YubikoOtpKeyPresenter has no YubikoOtpKeyConfigPtr.");
	BOOST_LOG_TRIVIAL(error)<< myErrMsg;
	throw std::runtime_error(myErrMsg);
}

inline string deleteSpaces(std::string pStr) {
	pStr.erase(remove(pStr.begin(), pStr.end(), ' '), pStr.end());
	return pStr;
}

void YubikoOtpKeyPresenter::accepted(const bool pAccepted) {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::accepted");
	BOOST_LOG_TRIVIAL(info)<< "Accepted==" << pAccepted;
	if (pAccepted) {
		if (m_CurCfg == 0) {
			throwNoConfig();
		}
		try {
			if (m_Mode == Add || m_Mode == Edit) {
				string myPrivateId { deleteSpaces(getPrivateId()) };
				getCurCfg().setPrivateId(myPrivateId);

				string mySecretKey { deleteSpaces(getSecretKey()) };
				getCurCfg().setSecretKey(mySecretKey);

				string myPublicId { deleteSpaces(getPublicId()) };
				getCurCfg().setPublicId(myPublicId);

				getCurCfg().setDescription(getDescription());

				getCurCfg().save();
			}
			saved();
		} catch (const std::exception& pExc) {
			auto myMsgView=getFactory().createMessageView();
			myMsgView->showMessage(
					translate("Trihlav error!"), pExc.what());
		} catch (...) {
			getFactory().createMessageView()->showMessage(
					translate("Trihlav error!"),
					translate("Unknown exception caught!"));
		}
		m_Mode = None;
	}
}

string YubikoOtpKeyPresenter::getPrivateId() {
	return getEdtPrivateId().getValue();
}

string YubikoOtpKeyPresenter::getPublicId() {
	return getEdtPublicId().getValue();
}

std::string YubikoOtpKeyPresenter::getSecretKey() {
	return getEdtSecretKey().getValue();
}

void YubikoOtpKeyPresenter::generatePrivateId() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::generatePrivateId");
	string myNewId;
	generate(YUBIKEY_UID_SIZE, myNewId);
	getEdtPrivateId().setValue(myNewId);
}

/**
 * Free text, will not be interpreted technically.
 * @return Users description of the key.
 */
string YubikoOtpKeyPresenter::getDescription() {
	const string myRetVal = getView().getEdtDescription().getValue();
	return myRetVal;
}

YubikoOtpKeyViewIface& YubikoOtpKeyPresenter::getView() {
	if (!m_View) {
		m_View = getFactory().createYubikoOtpKeyView();
		BOOST_LOG_TRIVIAL(debug)<< "Allocated view " << m_View.get();
		initUi();
	}
	return *m_View;
}

StrEditIface& YubikoOtpKeyPresenter::getEdtPrivateId() {
	return getView().getEdtPrivateId();
}

StrEditIface& YubikoOtpKeyPresenter::getEdtPublicId() {
	return getView().getEdtPublicId();
}

int YubikoOtpKeyPresenter::getPublicIdLen() {
	return getView().getSbxPublicIdLen().getValue();
}
void YubikoOtpKeyPresenter::generatePublicId() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::generatePublicId");
	const int mySz = getPublicIdLen();
	string myNewId;
	generateModhex(mySz, myNewId);
	getEdtPublicId().setValue(myNewId);
}

StrEditIface& YubikoOtpKeyPresenter::getEdtSecretKey() {
	return getView().getEdtSecretKey();
}

void YubikoOtpKeyPresenter::generateSecretKey() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::generateSecretKey");
	string myNewKey;
	generate(YUBIKEY_KEY_SIZE, myNewKey);
	getEdtSecretKey().setValue(myNewKey);
}

/**
 * The size is currently cut at 4096.
 * @param pBytes how long should the generated byte array be.
 * @param pTarget generate the hex encoded byte array here.
 */
void YubikoOtpKeyPresenter::generate(int pBytes, string& pTarget) {
	auto randchar = []() -> char
	{
		const char charset[] = "0123456789abcdef";
		const size_t myMaxIdx = (sizeof(charset) - 1);
		return charset[ rand() % myMaxIdx ];
	};
	const size_t myLen = min(2 * pBytes, 4094);
	pTarget.resize(myLen);
	generate_n(pTarget.begin(), myLen, randchar);
}

/**
 * The size is currently cut at 4096.
 * @param pBytes how long should the generated byte array be.
 * @param pTarget generate the hex encoded byte array here.
 */
void YubikoOtpKeyPresenter::generateModhex(int pBytes, string& pTarget) {
	auto randchar = []() -> char
	{
		const char charset[] = YUBIKEY_MODHEX_MAP;
		const size_t myMaxIdx = (sizeof(charset) - 1);
		return charset[ rand() % myMaxIdx ];
	};
	const size_t myLen = min(2 * pBytes, 4094);
	pTarget.resize(myLen);
	generate_n(pTarget.begin(), myLen, randchar);
}

MessageViewIface& YubikoOtpKeyPresenter::getMessageView() {
	if(!m_MessageView) {
		m_MessageView=getFactory().createMessageView();
	}
	return *m_MessageView;
}

SysUserListPresenter& YubikoOtpKeyPresenter::getSysUserListPresenter() {
	if(!m_SysUserListPresenter) {
		m_SysUserListPresenter.reset( new SysUserListPresenter(getFactory()));
		m_SysUserListPresenter->userSelectedSig.connect([this](){systemUserSelected();});
	}
	return *m_SysUserListPresenter;
}


}/* namespace trihlav */
