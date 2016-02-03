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
#include "trihlavLib/trihlavIEdit.hpp"
#include "trihlavLib/trihlavISpinBox.hpp"
#include "trihlavLib/trihlavIFactory.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavKeyManager.hpp"

using namespace std;

namespace trihlav {

YubikoOtpKeyPresenter::YubikoOtpKeyPresenter(const IFactory& pFactory )
    : IYubikoOtpKeyPresenter(pFactory)
    , itsView(pFactory.createYubikoOtpKeyView())
    , itsCurCfg(new YubikoOtpKeyConfig(pFactory.getKeyManager().getConfigDir())){
    BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::YubikoOptKeyPresenter");
    itsView->getPrivateId().setValue("");
    itsView->getSecretKey().setValue("");
    itsView->getPublicId().setValue("");
    itsView->getPublicIdLen().setValue(6);
    itsView->getAcceptedSignal().connect([=](const bool pAccepted) {
        accepted(pAccepted);
    });
}

YubikoOtpKeyPresenter::~YubikoOtpKeyPresenter() {
    BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::~YubikoOptKeyPresenter");
}

void YubikoOtpKeyPresenter::addKey() {
    itsView->show();
}

void YubikoOtpKeyPresenter::accepted(const bool pAccepted)
{
    BOOST_LOG_NAMED_SCOPE("YubikoOptKeyPresenter::accepted");
    BOOST_LOG_TRIVIAL(info) << "Accepted==" << pAccepted ;

}

} /* namespace trihlav */
