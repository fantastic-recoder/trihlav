/*
 * trihlavYubikoOptKeyPresenter.cpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#include <iostream>

#include "trihlavYubikoOtpKeyPresenter.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/locale/message.hpp>
#include <boost/format.hpp>

#include "trihlavIYubikoOtpKeyView.hpp"
#include "trihlavLib/trihlavIButton.hpp"
#include "trihlavLib/trihlavIEdit.hpp"
#include "trihlavLib/trihlavISpinBox.hpp"
#include "trihlavLib/trihlavIFactory.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavKeyManager.hpp"

using namespace std;
using namespace boost;
using namespace boost::locale;

namespace trihlav {

void YubikoOtpKeyPresenter::initUi() {
	getView().getEdtPrivateId().setValue("");
	getView().getEdtSecretKey().setValue("");
	getView().getEdtPublicId().setValue("");
	getView().getSbxPublicIdLen().setValue(6);
	getView().getSbxPublicIdLen().setMin(0);
	getView().getSbxPublicIdLen().setMax(6);
	getView().getSbxPublicIdLen().setStep(1);
	getView().getAcceptedSignal().connect([=](const bool pAccepted) {
		accepted(pAccepted);
	});
	getView().getBtnGenPrivateId().getPressedSignal().connect([=]() {
		generatePrivateId();
	});
	getView().getBtnGenPublicId().getPressedSignal().connect([=]() {
		generatePublicId();
	});
	getView().getBtnGenSecretKey().getPressedSignal().connect([=]() {
		generateSecretKey();
	});
}

YubikoOtpKeyPresenter::YubikoOtpKeyPresenter(const IFactory& pFactory) :
		YubikoOtpKeyPresenterI(pFactory), itsView(0),itsCurCfg(0)  {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::YubikoOptKeyPresenter");
}

YubikoOtpKeyPresenter::~YubikoOtpKeyPresenter() {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::~YubikoOptKeyPresenter");
	delete itsView;
	delete itsCurCfg;
}

void YubikoOtpKeyPresenter::addKey() {
	bfs::path myFilename(
			getFactory().getKeyManager().getConfigDir() / "%%-%%-%%");
	myFilename = bfs::unique_path(myFilename);
	itsCurCfg=new YubikoOtpKeyConfig(myFilename);
	getView().show();
}

YubikoOtpKeyConfig& YubikoOtpKeyPresenter::getCurCfg() {
	if(!itsCurCfg) {

	}
  return *itsCurCfg;
}

void YubikoOtpKeyPresenter::deleteKey() {
	if (itsCurCfg) {
		const path myFilename = getCurCfg().getFilename();
		if (exists(myFilename)) {
			if (!remove(myFilename)) {
				auto myErrMsg = format(
						translate("Failed to delete file %1%.")) % myFilename.native();
				BOOST_LOG_TRIVIAL(error)<< myErrMsg;
				throw new std::runtime_error(myErrMsg.str());
			}
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
	throw new std::runtime_error(myErrMsg);
}

void YubikoOtpKeyPresenter::accepted(const bool pAccepted) {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::accepted");
	BOOST_LOG_TRIVIAL(info)<< "Accepted==" << pAccepted;
	if (pAccepted) {
		if (itsCurCfg==0) {
			throwNoConfig();
		}
		getCurCfg().setPrivateId(getPrivateId());
		getCurCfg().setSecretKey(getSecretKey());
		getCurCfg().setPublicId(getPublicId());
		getCurCfg().setDescription(getDescription());
		getCurCfg().save();
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

IYubikoOtpKeyView& YubikoOtpKeyPresenter::getView() {
	if(itsView==0) {
		itsView=getFactory().createYubikoOtpKeyView();
		initUi();
	}
	return *itsView;
}

IStrEdit& YubikoOtpKeyPresenter::getEdtPrivateId() {
	return getView().getEdtPrivateId();
}

IStrEdit& YubikoOtpKeyPresenter::getEdtPublicId() {
	return getView().getEdtPublicId();
}

int YubikoOtpKeyPresenter::getPublicIdLen() {
	return getView().getSbxPublicIdLen().getValue();
}
void YubikoOtpKeyPresenter::generatePublicId() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::generatePublicId");
	const int mySz = getPublicIdLen();
	string myNewId;
	generate(mySz, myNewId);
	getEdtPublicId().setValue(myNewId);
}

IStrEdit& YubikoOtpKeyPresenter::getEdtSecretKey() {
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

}/* namespace trihlav */
