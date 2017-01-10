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
#ifndef TRIHLAV_MOCK_YUBIKO_OTP_KEY_VIEW_HPP_
#define TRIHLAV_MOCK_YUBIKO_OTP_KEY_VIEW_HPP_

#include <gmock/gmock.h>
#include "../../main/cpp/trihlavLib/trihlavYubikoOtpKeyViewIface.hpp"

#include "trihlavMockButton.hpp"
#include "trihlavMockSpinBox.hpp"
#include "trihlavMockStrEdit.hpp"


namespace trihlav {

struct MockYubikoOtpKeyView: virtual public YubikoOtpKeyViewIface {

	MockStrEdit itsMockEdtPrivateId;
	MockStrEdit itsMockEdtPublicId;
	MockStrEdit itsMockEdtDescription;
	MockStrEdit itsMockEdtSecretKey;
	MockStrEdit itsMockEdtSysUser;
	MockSpinBox itsMockSbxPublicIdLen;
	MockButton itsMockBtnGenPrivateId;
	MockButton itsMockBtnGenPublicId;
	MockButton itsMockBtnGenSecretKey;
	MockButton itsMockBtnSelectSysUser;
	MockButton itsMockBtnOk;
	MockButton itsMockBtnCancel;

	MockYubikoOtpKeyView();

	MOCK_CONST_METHOD0( getEdtPublicId, const StrEditIface& () );
	MOCK_METHOD0(getEdtPublicId,StrEditIface& () );

	MOCK_METHOD0(getSbxPublicIdLen, SpinBoxIface& () );
	MOCK_CONST_METHOD0(getSbxPublicIdLen, const SpinBoxIface& () );

	MOCK_CONST_METHOD0(getEdtPrivateId, const  StrEditIface& () );
	MOCK_METHOD0(getEdtPrivateId, StrEditIface& () );

	MOCK_CONST_METHOD0(getEdtSecretKey, const  StrEditIface& () );
	MOCK_METHOD0(getEdtSecretKey, StrEditIface& () );

	MOCK_CONST_METHOD0(getEdtDescription, const  StrEditIface& () );
	MOCK_METHOD0(getEdtDescription, StrEditIface& () );

	MOCK_CONST_METHOD0(getBtnGenPublicId, const  ButtonIface& () );
	MOCK_METHOD0(getBtnGenPublicId, ButtonIface& () );

	MOCK_CONST_METHOD0(getBtnGenPrivateId, const  ButtonIface& () );
	MOCK_METHOD0(getBtnGenPrivateId, ButtonIface& () );

	MOCK_CONST_METHOD0(getBtnGenSecretKey, const  ButtonIface& () );
	MOCK_METHOD0(getBtnGenSecretKey, ButtonIface& () );

	MOCK_CONST_METHOD0(getEdtSysUser,  const StrEditIface& () );
	MOCK_METHOD0(getEdtSysUser, StrEditIface& () );

	MOCK_CONST_METHOD0(getBtnSelectSysUser, const  ButtonIface& () );
	MOCK_METHOD0(getBtnSelectSysUser, ButtonIface& () );

	MOCK_CONST_METHOD0(getBtnOk, const  ButtonIface& () );
	MOCK_METHOD0(getBtnOk, ButtonIface& () );

	MOCK_CONST_METHOD0(getBtnCancel, const  ButtonIface& () );
	MOCK_METHOD0(getBtnCancel, ButtonIface& () );

	MOCK_METHOD0(show, void ());

	virtual ~MockYubikoOtpKeyView();

	void setupDefaultOnCallHandlers();
};

}  // namespace trihlav



#endif /* TRIHLAV_MOCK_YUBIKO_OTP_KEY_VIEW_HPP_ */
