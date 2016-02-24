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

#include <Wt/WDialog>

#include "../trihlavLib/trihlavYubikoOtpKeyViewIface.hpp"

namespace Wt {
	class WDialog;
}

namespace trihlav {

class WtStrEdit;
class WtPushButton;
class WtSpinBox;

class WtYubikoOtpKeyView: public YubikoOtpKeyViewIface {
    std::unique_ptr<Wt::WDialog> itsDlg;
	WtStrEdit* itsPublicId;
	WtStrEdit* itsEdtDescription;
	WtSpinBox* itsPublicIdLen;
	WtStrEdit* itsPrivateId;
	WtStrEdit* itsSecretKey;
	WtPushButton* itsGenPublicIdentityBtn;
	WtPushButton* itsGenPrivateIdentityBtn;
	WtPushButton* itsCancelBtn;
	WtPushButton* itsSaveBtn;
	WtPushButton* itsGenSecretKeyBtn;
public:
	WtYubikoOtpKeyView();
	virtual ~WtYubikoOtpKeyView();

	virtual const StrEditIface& getEdtPublicId() const;
	virtual StrEditIface& getEdtPublicId();

	virtual SpinBoxIface& getSbxPublicIdLen();
	virtual const SpinBoxIface& getSbxPublicIdLen() const;

	virtual const StrEditIface& getEdtPrivateId() const;
	virtual StrEditIface& getEdtPrivateId();

	virtual const StrEditIface& getEdtSecretKey() const;
	virtual StrEditIface& getEdtSecretKey();

	virtual const ButtonIface&  getBtnGenPublicId() const;
	virtual ButtonIface&  getBtnGenPublicId();

	virtual const ButtonIface&  getBtnGenPrivateId() const;
	virtual ButtonIface&  getBtnGenPrivateId();

	virtual const ButtonIface&  getBtnGenSecretKey() const;
	virtual ButtonIface&  getBtnGenSecretKey();

	virtual const ButtonIface&  getBtnCancel() const;
	virtual ButtonIface&  getBtnCancel();

	virtual const ButtonIface&  getBtnSave() const;
	virtual ButtonIface&  getBtnSave();

	virtual StrEditIface& getEdtDescription() ;
	virtual const StrEditIface& getEdtDescription() const ;

	virtual void show();

private:
    virtual void finishedSlot(Wt::WDialog::DialogCode pCode);
};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_YUBIKO_OTP_KEY_VIEW_HPP_ */
