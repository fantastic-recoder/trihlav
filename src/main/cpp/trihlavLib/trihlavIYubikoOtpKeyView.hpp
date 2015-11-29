/*
 * trihlavIYubikoOptKeyView.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_I_YUBIKO_OTP_KEY_VIEW_HPP_
#define TRIHLAV_I_YUBIKO_OTP_KEY_VIEW_HPP_

#include <trihlavLib/trihlavIEdit.hpp>
#include <trihlavLib/trihlavIButton.hpp>

namespace trihlav {

class IYubikoOtpKeyView {
public:
	virtual const IStrEdit& getPublicId() const=0;
	virtual IStrEdit& getPublicId()=0;

	virtual IEdit<int>& getPublicIdLen()=0;
	virtual const IEdit<int>& getPublicIdLen() const=0;

	virtual const IStrEdit& getPrivateId() const=0;
	virtual IStrEdit& getPrivateId()=0;

	virtual const IStrEdit& getSecretKey() const=0;
	virtual IStrEdit& getSecretKey()=0;

	virtual const IButton&  getGenPublicIdentityBtn() const =0;
	virtual IButton&  getGenPublicIdentityBtn() =0;

	virtual const IButton&  getGenPrivateIdentityBtn() const =0;
	virtual IButton&  getGenPrivateIdentityBtn() =0;

	virtual const IButton&  getGenSecretKeyBtn() const =0;
	virtual IButton&  getGenSecretKeyBtn() =0;

	virtual const IButton&  getCancelBtn() const =0;
	virtual IButton&  getCancelBtn() =0;

	virtual const IButton&  getSaveBtn() const =0;
	virtual IButton&  getSaveBtn() =0;

	virtual ~IYubikoOtpKeyView()=0;

};

} /* namespace trihlavApi */

#endif /* TRIHLAV_I_YUBIKO_OTP_KEY_VIEW_HPP_ */
