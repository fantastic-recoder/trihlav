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

#include <boost/locale.hpp>

#include <Wt/WGridLayout.h>
#include <Wt/WDialog.h>
#include <Wt/WLabel.h>

#include "trihlavWtStrEdit.hpp"
#include "trihlavWtSpinBox.hpp"
#include "trihlavWtPushButton.hpp"
#include "trihlavWtYubikoOtpKeyView.hpp"

using namespace Wt;
using namespace std;
using namespace boost;
using boost::locale::translate;

using U = Wt::WLength::Unit;

namespace trihlav {

WtYubikoOtpKeyView::WtYubikoOtpKeyView() :
		m_PublicId(new WtStrEdit), //
		m_PublicIdLen(new WtSpinBox), //
		m_PrivateId(new WtStrEdit), //
		m_SecretKey(new WtStrEdit), //
		m_EdtDescription(new WtStrEdit), //
		m_GenPublicIdentityBtn(new WtPushButton(translate("Generate"))), //
		m_GenPrivateIdentityBtn(new WtPushButton(translate("Generate"))), //
		m_EdtSysUser(new WtStrEdit), //
		m_BtnSelectSysUser(new WtPushButton(translate("Select system user"))), //
		m_GenSecretKeyBtn(new WtPushButton(translate("Generate"))) //
{
    getDlg().setWindowTitle(translate("Add key").str());
	getDlg().setWidth(WLength(64, U::FontEm));
    auto myTopLayout = new WGridLayout;
    {
        std::unique_ptr<Wt::WLabel> myLbl(new WLabel(translate("Description").str()));
		myLbl->setWidth(WLength(9.0,U::FontEm));
        myTopLayout->addWidget(std::move(myLbl), 0, 0, 1, 1, Wt::AlignmentFlag::Right | Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_EdtDescription), 0, 1, 1, 5, Wt::AlignmentFlag::Middle);
	}
	{
		m_GenPublicIdentityBtn->setWidth(WLength(9.0,U::FontEm));
		m_PublicId->setWidth(WLength(13.0,U::FontEm));
		m_PublicId->setInputMask("<aa aa aa aa aa aa");
		m_PublicId->addStyleClass("console-font");
		m_PublicIdLen->setWidth(WLength(2.0,U::FontEm));
		Wt::WLabel* myLbl = new WLabel(translate("Public ID (modhex)").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
        myTopLayout->addWidget(std::unique_ptr<WWidget>(myLbl), 1, 0, 1, 1,
                               Wt::AlignmentFlag::Right | Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_PublicId), 1, 1, 1, 3, Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_PublicIdLen), 1, 4, 1, 1,
                               Wt::AlignmentFlag::Left | Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_GenPublicIdentityBtn), 1, 5, 1, 1, Wt::AlignmentFlag::Top);
	}
	{
		m_GenPrivateIdentityBtn->setWidth(WLength(9.0,U::FontEm));
		m_PrivateId->setWidth(WLength(18.0,U::FontEm));
		m_PrivateId->setInputMask("<hh hh hh hh hh hh");
		m_PrivateId->addStyleClass("console-font");
		Wt::WLabel* myLbl = new WLabel(translate("Private ID").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
        myTopLayout->addWidget(std::unique_ptr<WWidget>(myLbl), 2, 0, 1, 1,
                               Wt::AlignmentFlag::Right | Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_PrivateId), 2, 1, 1, 4, Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_GenPrivateIdentityBtn), 2, 5, 1, 1, Wt::AlignmentFlag::Top);
	}
	{
		m_GenSecretKeyBtn->setWidth(WLength(9.0,U::FontEm));
		m_SecretKey->setWidth(WLength(18.0,U::FontEm));
		m_SecretKey->setInputMask("<hh hh hh hh hh hh hh hh hh hh hh hh hh hh hh hh");
		m_SecretKey->addStyleClass("console-font");
		Wt::WText* myLbl = new WText(translate("Secret key").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
        myTopLayout->addWidget(std::unique_ptr<WWidget>(myLbl), 3, 0, 1, 1,
                               Wt::AlignmentFlag::Right | Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_SecretKey), 3, 1, 1, 4, Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_GenSecretKeyBtn), 3, 5, 1, 1, Wt::AlignmentFlag::Top);
	}
	{
		m_BtnSelectSysUser->setWidth(WLength(9.0,U::FontEm));
		m_EdtSysUser->setWidth(WLength(18.0,U::FontEm));
		m_EdtSysUser->setReadOnly(true);
		Wt::WText* myLbl = new WText(translate("Operating system user").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
        myTopLayout->addWidget(std::unique_ptr<WWidget>(myLbl), 4, 0, 1, 1,
                               Wt::AlignmentFlag::Right | Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_EdtSysUser), 4, 1, 1, 3, Wt::AlignmentFlag::Middle);
        myTopLayout->addWidget(std::unique_ptr<WWidget>(m_BtnSelectSysUser), 4, 4, 1, 2, Wt::AlignmentFlag::Top);
    }
    getDlg().contents()->setLayout(std::unique_ptr<Wt::WLayout>(myTopLayout));
}

    WtYubikoOtpKeyView::~WtYubikoOtpKeyView() = default;

const StrEditIface& WtYubikoOtpKeyView::getEdtPublicId() const {
	return *m_PublicId;
}

StrEditIface& WtYubikoOtpKeyView::getEdtPublicId() {
	return *m_PublicId;
}

SpinBoxIface& WtYubikoOtpKeyView::getSbxPublicIdLen() {
	return *m_PublicIdLen;
}

const SpinBoxIface& WtYubikoOtpKeyView::getSbxPublicIdLen() const {
	return *m_PublicIdLen;
}

const StrEditIface& WtYubikoOtpKeyView::getEdtPrivateId() const {
	return *m_PrivateId;
}

StrEditIface& WtYubikoOtpKeyView::getEdtPrivateId() {
	return *m_PrivateId;
}

const StrEditIface& WtYubikoOtpKeyView::getEdtSecretKey() const {
	return *m_SecretKey;
}

StrEditIface& WtYubikoOtpKeyView::getEdtSecretKey() {
	return *m_SecretKey;
}

const ButtonIface& WtYubikoOtpKeyView::getBtnGenPublicId() const {
	return *m_GenPublicIdentityBtn;
}

ButtonIface& WtYubikoOtpKeyView::getBtnGenPublicId() {
	return *m_GenPublicIdentityBtn;
}

const ButtonIface& WtYubikoOtpKeyView::getBtnGenPrivateId() const {
	return *m_GenPrivateIdentityBtn;
}

ButtonIface& WtYubikoOtpKeyView::getBtnGenPrivateId() {
	return *m_GenPrivateIdentityBtn;
}

const ButtonIface& WtYubikoOtpKeyView::getBtnGenSecretKey() const {
	return *m_GenSecretKeyBtn;
}

ButtonIface& WtYubikoOtpKeyView::getBtnGenSecretKey() {
	return *m_GenSecretKeyBtn;
}

const StrEditIface& WtYubikoOtpKeyView::getEdtSysUser() const {
	return *m_EdtSysUser;
}

StrEditIface& WtYubikoOtpKeyView::getEdtSysUser() {
	return *m_EdtSysUser;
}

const ButtonIface& WtYubikoOtpKeyView::getBtnSelectSysUser() const {
	return *m_BtnSelectSysUser;
}

ButtonIface& WtYubikoOtpKeyView::getBtnSelectSysUser() {
	return *m_BtnSelectSysUser;
}

StrEditIface& WtYubikoOtpKeyView::getEdtDescription() {
	return *m_EdtDescription;
}

const StrEditIface& WtYubikoOtpKeyView::getEdtDescription() const {
	return *m_EdtDescription;
}

} /* namespace trihlav */

