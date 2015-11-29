/*
 * trihlavYubikoOptKeyPresenter.cpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#include "trihlavYubikoOtpKeyPresenter.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavIYubikoOtpKeyView.hpp"

namespace trihlav {

YubikoOtpKeyPresenter::YubikoOtpKeyPresenter(IYubikoOtpKeyView& pView ): itsView(pView) {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::YubikoOptKeyPresenter");
	pView.getPrivateId().setValue("");
	pView.getSecretKey().setValue("");
	pView.getPublicId().setValue("");
	pView.getPublicIdLen().setValue(6);
}

YubikoOtpKeyPresenter::~YubikoOtpKeyPresenter() {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::~YubikoOptKeyPresenter");
}

} /* namespace trihlav */
