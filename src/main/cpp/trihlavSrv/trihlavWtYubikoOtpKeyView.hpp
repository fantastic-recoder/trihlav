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

#include "trihlavLib/trihlavIYubikoOtpKeyView.hpp"

namespace Wt {
	class WDialog;
}

namespace trihlav {

class WtStrEdit;
class WtPushButton;

class WtYubikoOtpKeyView: public IYubikoOtpKeyView {
	Wt::WDialog*   itsDlg;
	WtStrEdit* itsPublicId;
	WtStrEdit* itsPublicIdLen;
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

	virtual const IStrEdit& getPublicId() const;
	virtual IStrEdit& getPublicId();

	virtual IStrEdit& getPublicIdLen();
	virtual const IStrEdit& getPublicIdLen() const;

	virtual const IStrEdit& getPrivateId() const;
	virtual IStrEdit& getPrivateId();

	virtual const IStrEdit& getSecretKey() const;
	virtual IStrEdit& getSecretKey();

	virtual const IButton&  getGenPublicIdentityBtn() const;
	virtual IButton&  getGenPublicIdentityBtn();

	virtual const IButton&  getGenPrivateIdentityBtn() const;
	virtual IButton&  getGenPrivateIdentityBtn();

	virtual const IButton&  getGenSecretKeyBtn() const;
	virtual IButton&  getGenSecretKeyBtn();

	virtual const IButton&  getCancelBtn() const;
	virtual IButton&  getCancelBtn();

	virtual const IButton&  getSaveBtn() const;
	virtual IButton&  getSaveBtn();

	virtual void show();
};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_YUBIKO_OTP_KEY_VIEW_HPP_ */
