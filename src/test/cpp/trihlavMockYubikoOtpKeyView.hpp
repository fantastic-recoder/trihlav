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

#include "trihlavMockButton.hpp"
#include "trihlavMockSpinBox.hpp"
#include "trihlavMockStrEdit.hpp"

#include "trihlavLib/trihlavIYubikoOtpKeyView.hpp"

namespace trihlav {

struct MockYubikoOtpKeyView: virtual public IYubikoOtpKeyView {

	MockStrEdit itsMockEdtPrivateId;
	MockStrEdit itsMockEdtPublicId;
	MockStrEdit itsMockEdtDescription;
	MockStrEdit itsMockEdtSecretKey;
	MockSpinBox itsMockSbxPublicIdLen;
	MockButton itsMockBtnGenPrivateId;
	MockButton itsMockBtnGenPublicId;
	MockButton itsMockBtnGenSecretKey;
	MockButton itsMockBtnSave;
	MockButton itsMockBtnCancel;

	MockYubikoOtpKeyView();

	MOCK_CONST_METHOD0( getEdtPublicId, const IStrEdit& () );
	MOCK_METHOD0(getEdtPublicId,IStrEdit& () );

	MOCK_METHOD0(getSbxPublicIdLen, ISpinBox& () );
	MOCK_CONST_METHOD0(getSbxPublicIdLen, const ISpinBox& () );

	MOCK_CONST_METHOD0(getEdtPrivateId, const  IStrEdit& () );
	MOCK_METHOD0(getEdtPrivateId, IStrEdit& () );

	MOCK_CONST_METHOD0(getEdtSecretKey, const  IStrEdit& () );
	MOCK_METHOD0(getEdtSecretKey, IStrEdit& () );

	MOCK_CONST_METHOD0(getEdtDescription, const  IStrEdit& () );
	MOCK_METHOD0(getEdtDescription, IStrEdit& () );

	MOCK_CONST_METHOD0(getBtnGenPublicId, const  IButton& () );
	MOCK_METHOD0(getBtnGenPublicId, IButton& () );

	MOCK_CONST_METHOD0(getBtnGenPrivateId, const  IButton& () );
	MOCK_METHOD0(getBtnGenPrivateId, IButton& () );

	MOCK_CONST_METHOD0(getBtnGenSecretKey, const  IButton& () );
	MOCK_METHOD0(getBtnGenSecretKey, IButton& () );

	MOCK_CONST_METHOD0(getBtnCancel,  const IButton& () );
	MOCK_METHOD0(getBtnCancel, IButton& () );

	MOCK_CONST_METHOD0(getBtnSave, const  IButton& () );
	MOCK_METHOD0(getBtnSave, IButton& () );

	MOCK_METHOD0(show, void ());

	virtual ~MockYubikoOtpKeyView();
};

}  // namespace trihlav



#endif /* TRIHLAV_MOCK_YUBIKO_OTP_KEY_VIEW_HPP_ */
