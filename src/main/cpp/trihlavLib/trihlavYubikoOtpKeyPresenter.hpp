/*
 * trihlavYubikoOptKeyPresenter.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_
#define TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_

namespace trihlav {

class IYubikoOtpKeyView;

class YubikoOtpKeyPresenter {
	IYubikoOtpKeyView& itsView;
public:
	YubikoOtpKeyPresenter(IYubikoOtpKeyView& pView);
	virtual ~YubikoOtpKeyPresenter();
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_ */
