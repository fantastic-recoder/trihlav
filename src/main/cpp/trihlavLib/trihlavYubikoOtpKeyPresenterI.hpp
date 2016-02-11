/*
 * trihlavIYubikoOtpKeyPresenter.hpp
 *
 *  Created on: 27.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_I_YUBIKO_OTP_KEY_PRESENTER_HPP_
#define TRIHLAV_I_YUBIKO_OTP_KEY_PRESENTER_HPP_

#include "trihlavLib/trihlavIPresenter.hpp"

namespace trihlav {

class IYubikoOtpKeyView;

class YubikoOtpKeyPresenterI : public IPresenter {
public:
	YubikoOtpKeyPresenterI(const IFactory& pFactory):IPresenter(pFactory){}
	virtual void addKey()=0;
	virtual IYubikoOtpKeyView& getView()=0;

private:
};

}

#endif /* TRIHLAV_I_YUBIKO_OTP_KEY_PRESENTER_HPP_ */
