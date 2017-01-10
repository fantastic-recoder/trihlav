/*
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
	der GNU General Public License, wie von der Free Software Foundation,
	Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
	veröffentlichten Version, weiterverbreiten und/oder modifizieren.

	Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
	OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
	Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
	Siehe die GNU General Public License für weitere Details.

	Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
	Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/
#ifndef TRIHLAV_WT_YUBIKO_OTP_KEY_VIEW_HPP_
#define TRIHLAV_WT_YUBIKO_OTP_KEY_VIEW_HPP_

#include <memory>
#include <string>

#include "trihlavLib/trihlavYubikoOtpKeyViewIface.hpp"

#include "trihlavWtDialogView.hpp"


namespace trihlav {

class WtStrEdit;
class WtSpinBox;

class WtYubikoOtpKeyView: virtual public WtDialogView, virtual public YubikoOtpKeyViewIface {
	WtStrEdit* itsPublicId;
	WtStrEdit* itsEdtDescription;
	WtSpinBox* itsPublicIdLen;
	WtStrEdit* itsPrivateId;
	WtStrEdit* itsSecretKey;
	WtStrEdit* itsEdtSysUser;
	WtPushButton* itsGenPublicIdentityBtn;
	WtPushButton* itsGenPrivateIdentityBtn;
	WtPushButton* itsGenSecretKeyBtn;
	WtPushButton* itsBtnSelectSysUser;
	std::string   itsSysUserLogin;
public:
	WtYubikoOtpKeyView();
	virtual ~WtYubikoOtpKeyView();

	virtual const StrEditIface& getEdtPublicId() const override;
	virtual StrEditIface& getEdtPublicId() override;

	virtual SpinBoxIface& getSbxPublicIdLen() override;
	virtual const SpinBoxIface& getSbxPublicIdLen() const override;

	virtual const StrEditIface& getEdtPrivateId() const override;
	virtual StrEditIface& getEdtPrivateId() override;

	virtual const StrEditIface& getEdtSecretKey() const override;
	virtual StrEditIface& getEdtSecretKey() override;

	virtual const ButtonIface&  getBtnGenPublicId() const override;
	virtual ButtonIface&  getBtnGenPublicId() override;

	virtual const ButtonIface&  getBtnGenPrivateId() const override;
	virtual ButtonIface&  getBtnGenPrivateId() override;

	virtual const ButtonIface&  getBtnGenSecretKey() const override;
	virtual ButtonIface&  getBtnGenSecretKey() override;

	virtual const StrEditIface& getEdtSysUser() const  override;
	virtual StrEditIface& getEdtSysUser()  override;

	virtual const ButtonIface&  getBtnSelectSysUser() const  override;
	virtual ButtonIface&  getBtnSelectSysUser()  override;

	virtual StrEditIface& getEdtDescription()  override;
	virtual const StrEditIface& getEdtDescription() const  override;

};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_YUBIKO_OTP_KEY_VIEW_HPP_ */
