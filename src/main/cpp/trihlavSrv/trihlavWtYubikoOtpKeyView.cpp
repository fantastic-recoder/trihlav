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

#include <Wt/WGridLayout>
#include <Wt/WDialog>
#include <Wt/WLength>
#include <Wt/WLabel>

#include "trihlavWtStrEdit.hpp"
#include "trihlavWtSpinBox.hpp"
#include "trihlavWtPushButton.hpp"
#include "trihlavWtYubikoOtpKeyView.hpp"

using namespace Wt;
using namespace std;
using namespace boost;
using boost::locale::translate;

typedef Wt::WLength::Unit U;

namespace trihlav {

WtYubikoOtpKeyView::WtYubikoOtpKeyView() :
		itsDlg(new WDialog), //
		itsPublicId(new WtStrEdit), //
		itsPublicIdLen(new WtSpinBox), //
		itsPrivateId(new WtStrEdit), //
		itsSecretKey(new WtStrEdit), //
		itsEdtDescription(new WtStrEdit), //
		itsGenPublicIdentityBtn(new WtPushButton(translate("Generate"))), //
		itsGenPrivateIdentityBtn(new WtPushButton(translate("Generate"))), //
		itsCancelBtn(new WtPushButton(translate("Cancel"))), //
		itsSaveBtn(new WtPushButton(translate("Save"))), //
		itsGenSecretKeyBtn(new WtPushButton(translate("Generate"))) //
{
	itsDlg->setCaption(translate("Add key").str());
	itsDlg->setWidth(WLength(64, U::FontEm));
	WGridLayout* myTopLayout = new WGridLayout;
	{
		Wt::WLabel* myLbl = new WLabel(translate("Description").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
		myTopLayout->addWidget(myLbl,0,0,1,1,Wt::AlignRight|Wt::AlignMiddle);
		myTopLayout->addWidget(itsEdtDescription,0,1,1,5,Wt::AlignMiddle);
	}
	{
		itsGenPublicIdentityBtn->setWidth(WLength(9.0,U::FontEm));
		itsPublicId->setWidth(WLength(13.0,U::FontEm));
		itsPublicId->setInputMask("<aa aa aa aa aa aa");
		itsPublicId->addStyleClass("console-font");
		itsPublicIdLen->setWidth(WLength(2.0,U::FontEm));
		Wt::WLabel* myLbl = new WLabel(translate("Public ID (modhex)").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
		myTopLayout->addWidget(myLbl,1,0,1,1,Wt::AlignRight|Wt::AlignMiddle);
		myTopLayout->addWidget(itsPublicId,1,1,1,3,Wt::AlignMiddle);
		myTopLayout->addWidget(itsPublicIdLen,1,4,1,1,Wt::AlignLeft|Wt::AlignMiddle);
		myTopLayout->addWidget(itsGenPublicIdentityBtn,1,5,1,1,Wt::AlignTop);
	}
	{
		itsGenPrivateIdentityBtn->setWidth(WLength(9.0,U::FontEm));
		itsPrivateId->setWidth(WLength(18.0,U::FontEm));
		itsPrivateId->setInputMask("<hh hh hh hh hh hh");
		itsPrivateId->addStyleClass("console-font");
		Wt::WLabel* myLbl = new WLabel(translate("Private ID").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
		myTopLayout->addWidget(myLbl,2,0,1,1,Wt::AlignRight|Wt::AlignMiddle);
		myTopLayout->addWidget(itsPrivateId,2,1,1,4,Wt::AlignMiddle);
		myTopLayout->addWidget(itsGenPrivateIdentityBtn,2,5,1,1,Wt::AlignTop);
	}
	{
		itsGenSecretKeyBtn->setWidth(WLength(9.0,U::FontEm));
		itsSecretKey->setWidth(WLength(18.0,U::FontEm));
		itsSecretKey->setInputMask("<hh hh hh hh hh hh hh hh hh hh hh hh hh hh hh hh");
		itsSecretKey->addStyleClass("console-font");
		Wt::WText* myLbl = new WText(translate("Secret key").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
		myTopLayout->addWidget(myLbl,3,0,1,1,Wt::AlignRight|Wt::AlignMiddle);
		myTopLayout->addWidget(itsSecretKey,3,1,1,4,Wt::AlignMiddle);
		myTopLayout->addWidget(itsGenSecretKeyBtn,3,5,1,1,Wt::AlignTop);
	}
	{
		myTopLayout->addWidget(itsCancelBtn,4,1,1,1,Wt::AlignCenter|Wt::AlignMiddle);
		myTopLayout->addWidget(itsSaveBtn,4,4,1,1,Wt::AlignCenter|Wt::AlignMiddle);
		itsCancelBtn->resize(WLength(11.0,U::FontEm),WLength(2.0,U::FontEm));
		itsSaveBtn->resize(WLength(11.0,U::FontEm),WLength(2.0,U::FontEm));
	}
	itsDlg->contents()->setLayout(myTopLayout);
	itsDlg->finished().connect(this, &WtYubikoOtpKeyView::finishedSlot);
	itsCancelBtn->clicked().connect(itsDlg.get(), &WDialog::reject);
	itsSaveBtn->clicked().connect(itsDlg.get(), &WDialog::accept);
}

WtYubikoOtpKeyView::~WtYubikoOtpKeyView() {
	// TODO Auto-generated destructor stubb
}

const StrEditIface& WtYubikoOtpKeyView::getEdtPublicId() const {
	return *itsPublicId;
}

StrEditIface& WtYubikoOtpKeyView::getEdtPublicId() {
	return *itsPublicId;
}

SpinBoxIface& WtYubikoOtpKeyView::getSbxPublicIdLen() {
	return *itsPublicIdLen;
}

const SpinBoxIface& WtYubikoOtpKeyView::getSbxPublicIdLen() const {
	return *itsPublicIdLen;
}

const StrEditIface& WtYubikoOtpKeyView::getEdtPrivateId() const {
	return *itsPrivateId;
}

StrEditIface& WtYubikoOtpKeyView::getEdtPrivateId() {
	return *itsPrivateId;
}

const StrEditIface& WtYubikoOtpKeyView::getEdtSecretKey() const {
	return *itsSecretKey;
}

StrEditIface& WtYubikoOtpKeyView::getEdtSecretKey() {
	return *itsSecretKey;
}

const ButtonIface& WtYubikoOtpKeyView::getBtnGenPublicId() const {
	return *itsGenPublicIdentityBtn;
}

ButtonIface& WtYubikoOtpKeyView::getBtnGenPublicId() {
	return *itsGenPublicIdentityBtn;
}

const ButtonIface& WtYubikoOtpKeyView::getBtnGenPrivateId() const {
	return *itsGenPrivateIdentityBtn;
}

ButtonIface& WtYubikoOtpKeyView::getBtnGenPrivateId() {
	return *itsGenPrivateIdentityBtn;
}

const ButtonIface& WtYubikoOtpKeyView::getBtnGenSecretKey() const {
	return *itsGenSecretKeyBtn;
}

ButtonIface& WtYubikoOtpKeyView::getBtnGenSecretKey() {
	return *itsGenSecretKeyBtn;
}

const ButtonIface& WtYubikoOtpKeyView::getBtnCancel() const {
	return *itsCancelBtn;
}

ButtonIface& WtYubikoOtpKeyView::getBtnCancel() {
	return *itsCancelBtn;
}

const ButtonIface& WtYubikoOtpKeyView::getBtnSave() const {
	return *itsSaveBtn;
}

ButtonIface& WtYubikoOtpKeyView::getBtnSave() {
	return *itsSaveBtn;
}

void WtYubikoOtpKeyView::show() {
	itsDlg->show();
}

void WtYubikoOtpKeyView::finishedSlot(WDialog::DialogCode pCode) {
	getAcceptedSignal()(pCode == WDialog::DialogCode::Accepted);
}

StrEditIface& WtYubikoOtpKeyView::getEdtDescription() {
	return *itsEdtDescription;
}

const StrEditIface& WtYubikoOtpKeyView::getEdtDescription() const {
	return *itsEdtDescription;
}

} /* namespace trihlav */

