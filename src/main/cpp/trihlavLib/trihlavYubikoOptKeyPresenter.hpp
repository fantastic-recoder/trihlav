/*
 * trihlavYubikoOptKeyPresenter.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_
#define TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_

namespace trihlavApi {

class IYubikoOptKeyView;

class YubikoOptKeyPresenter {
	IYubikoOptKeyView& itsView;
public:
	YubikoOptKeyPresenter(IYubikoOptKeyView& pView);
	virtual ~YubikoOptKeyPresenter();
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_ */
