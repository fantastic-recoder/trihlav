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
#include "trihlavLib/trihlavIFactory.hpp"

namespace trihlav {

YubikoOtpKeyPresenter::YubikoOtpKeyPresenter(const IFactory& pFactory )
: IYubikoOtpKeyPresenter(pFactory)
, itsView(pFactory.createYubikoOtpKeyView()) {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::YubikoOptKeyPresenter");
	itsView->getPrivateId().setValue("");
	itsView->getSecretKey().setValue("");
	itsView->getPublicId().setValue("");
	itsView->getPublicIdLen().setValue("6");
}

YubikoOtpKeyPresenter::~YubikoOtpKeyPresenter() {
	BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::~YubikoOptKeyPresenter");
}

void YubikoOtpKeyPresenter::addKey() {
	itsView->show();
}

} /* namespace trihlav */
