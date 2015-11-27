/*
 * trihlavYubikoOptKeyPresenter.cpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavLib/trihlavYubikoOptKeyPresenter.hpp"
#include "trihlavLib/trihlavIYubikoOptKeyView.hpp"

namespace trihlav {

YubikoOptKeyPresenter::YubikoOptKeyPresenter(IYubikoOptKeyView& pView ): itsView(pView) {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::YubikoOptKeyPresenter");
	pView.getPrivateIdentity().setValue("");
//	pView.getSecretKey().setValue("");
//	pView.getPublicIdentity().setValue("");
//	pView.getPublicIdentityLen().setValue(6);
}

YubikoOptKeyPresenter::~YubikoOptKeyPresenter() {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::~YubikoOptKeyPresenter");
}

} /* namespace trihlav */
