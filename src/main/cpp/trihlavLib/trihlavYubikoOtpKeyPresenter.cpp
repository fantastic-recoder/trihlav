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

#include "trihlavIYubikoOtpKeyView.hpp"
#include "trihlavLib/trihlavIButton.hpp"
#include "trihlavLib/trihlavIEdit.hpp"
#include "trihlavLib/trihlavISpinBox.hpp"
#include "trihlavLib/trihlavIFactory.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavKeyManager.hpp"

using namespace std;

namespace trihlav {

YubikoOtpKeyPresenter::YubikoOtpKeyPresenter(const IFactory& pFactory) :
		IYubikoOtpKeyPresenter(pFactory), itsView(
				pFactory.createYubikoOtpKeyView()), itsCurCfg(
				new YubikoOtpKeyConfig(pFactory.getKeyManager().getConfigDir())) {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::YubikoOptKeyPresenter");
	itsView->getEdtPrivateId().setValue("");
	itsView->getEdtSecretKey().setValue("");
	itsView->getEdtPublicId().setValue("");
	itsView->getSbxPublicIdLen().setValue(6);
	itsView->getSbxPublicIdLen().setMin(0);
	itsView->getSbxPublicIdLen().setMax(6);
	itsView->getSbxPublicIdLen().setStep(1);
	itsView->getAcceptedSignal().connect([=](const bool pAccepted) {
		accepted(pAccepted);
	});
	itsView->getBtnGenPrivateId().getPressedSignal().connect([=]() {
		generatePrivateId();
	});
	itsView->getBtnGenPublicId().getPressedSignal().connect([=]() {
		generatePublicId();
	});
	itsView->getBtnGenSecretKey().getPressedSignal().connect([=]() {
		generateSecretKey();
	});
}

YubikoOtpKeyPresenter::~YubikoOtpKeyPresenter() {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::~YubikoOptKeyPresenter");
}

void YubikoOtpKeyPresenter::addKey() {
	itsView->show();
}

const IStrEdit& YubikoOtpKeyPresenter::getEdtSecretKey() const {
	return getView().getEdtSecretKey();
}

const std::string YubikoOtpKeyPresenter::getSecretKey() const {
	return getEdtSecretKey().getValue();
}

void YubikoOtpKeyPresenter::accepted(const bool pAccepted) {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::accepted");
	BOOST_LOG_TRIVIAL(info)<< "Accepted==" << pAccepted;
	if(pAccepted) {
		getCurCfg()->setPrivateId(getPrivateId());
		getCurCfg()->setSecretKey(getSecretKey());
		getCurCfg()->setPublicId(getPublicId());
	}
}

const string YubikoOtpKeyPresenter::getPrivateId() const {
	return getEdtPrivateId().getValue();
}

const string YubikoOtpKeyPresenter::getPublicId() const {
	return getEdtPublicId().getValue();
}

void YubikoOtpKeyPresenter::generatePrivateId() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::generatePrivateId");
	string myNewId;
	generate(YUBIKEY_UID_SIZE,myNewId);
	getEdtPrivateId().setValue(myNewId);
}

int YubikoOtpKeyPresenter::getPublicIdLen() const {
	const int myRetVal = getView().getSbxPublicIdLen().getValue();
	return myRetVal;
}

IYubikoOtpKeyView& YubikoOtpKeyPresenter::getView() {
	return *itsView;
}

const IYubikoOtpKeyView& YubikoOtpKeyPresenter::getView() const {
	return *itsView;
}

IStrEdit& YubikoOtpKeyPresenter::getEdtPrivateId() {
	return getView().getEdtPrivateId();
}

const IStrEdit& YubikoOtpKeyPresenter::getEdtPrivateId() const {
	return getView().getEdtPrivateId();
}

IStrEdit& YubikoOtpKeyPresenter::getEdtPublicId() {
	return getView().getEdtPublicId();
}

const IStrEdit& YubikoOtpKeyPresenter::getEdtPublicId() const {
	return getView().getEdtPublicId();
}

void YubikoOtpKeyPresenter::generatePublicId() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::generatePublicId");
	const int mySz = getPublicIdLen();
	string myNewId;
	generate(mySz,myNewId);
	getEdtPublicId().setValue(myNewId);
}

IStrEdit& YubikoOtpKeyPresenter::getEdtSecretKey() {
	return getView().getEdtSecretKey();
}

void YubikoOtpKeyPresenter::generateSecretKey() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::generateSecretKey");
	string myNewKey;
	generate(YUBIKEY_KEY_SIZE,myNewKey);
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
	const size_t myLen=min(2*pBytes,4094);
	pTarget.resize(myLen);
	generate_n( pTarget.begin(), myLen, randchar );
}

}/* namespace trihlav */
