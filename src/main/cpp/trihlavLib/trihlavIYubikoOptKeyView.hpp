/*
 * trihlavIYubikoOptKeyView.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_I_YUBIKO_OPT_KEY_VIEW_HPP_
#define TRIHLAV_I_YUBIKO_OPT_KEY_VIEW_HPP_

#include <trihlavLib/trihlavIEdit.hpp>
#include <trihlavLib/trihlavIButton.hpp>

namespace trihlav {

class IYubikoOptKeyView {
public:
	virtual const IStrEdit& getPublicIdentity() const=0;
	virtual IStrEdit& getPublicIdentity()=0;

	virtual IEdit<int>& getPublicIdentityLen()=0;
	virtual const IEdit<int>& getPublicIdentityLen() const=0;

	virtual const IStrEdit& getPrivateIdentity() const=0;
	virtual IStrEdit& getPrivateIdentity()=0;

	virtual const IStrEdit& getSecretKey() const=0;
	virtual IStrEdit& getSecretKey()=0;

	virtual const IButton&  getGenPublicIdentityBtn() const =0;
	virtual IButton&  getGenPublicIdentityBtn() =0;

	virtual const IButton&  getGenPrivateIdentityBtn() const =0;
	virtual IButton&  getGenPrivateIdentityBtn() =0;

	virtual const IButton&  getGenSecretKeyBtn() const =0;
	virtual IButton&  getGenSecretKeyBtn() =0;

	virtual ~IYubikoOptKeyView()=0;
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_I_YUBIKO_OPT_KEY_VIEW_HPP_ */
