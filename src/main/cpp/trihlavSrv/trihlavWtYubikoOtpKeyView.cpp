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
		itsPublicIdLen(new WtStrEdit), //
		itsPrivateId(new WtStrEdit), //
		itsSecretKey(new WtStrEdit), //
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
		itsGenPublicIdentityBtn->setWidth(WLength(9.0,U::FontEm));
		itsPublicId->setWidth(WLength(13.0,U::FontEm));
		itsPublicIdLen->setWidth(WLength(2.0,U::FontEm));
		Wt::WLabel* myLbl = new WLabel(translate("Public ID").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
		myTopLayout->addWidget(myLbl,0,0,1,1,Wt::AlignRight|Wt::AlignMiddle);
		myTopLayout->addWidget(itsPublicId,0,1,1,3,Wt::AlignMiddle);
		myTopLayout->addWidget(itsPublicIdLen,0,4,1,1,Wt::AlignLeft|Wt::AlignMiddle);
		myTopLayout->addWidget(itsGenPublicIdentityBtn,0,5,1,1,Wt::AlignTop);
	}
	{
		itsGenPrivateIdentityBtn->setWidth(WLength(9.0,U::FontEm));
		itsPrivateId->setWidth(WLength(18.0,U::FontEm));
		Wt::WLabel* myLbl = new WLabel(translate("Private ID").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
		myTopLayout->addWidget(myLbl,1,0,1,1,Wt::AlignRight|Wt::AlignMiddle);
		myTopLayout->addWidget(itsPrivateId,1,1,1,4,Wt::AlignMiddle);
		myTopLayout->addWidget(itsGenPrivateIdentityBtn,1,5,1,1,Wt::AlignTop);
	}
	{
		itsGenSecretKeyBtn->setWidth(WLength(9.0,U::FontEm));
		itsSecretKey->setWidth(WLength(18.0,U::FontEm));
		Wt::WText* myLbl = new WText(translate("Secret key").str());
		myLbl->setWidth(WLength(9.0,U::FontEm));
		myTopLayout->addWidget(myLbl,2,0,1,1,Wt::AlignRight|Wt::AlignMiddle);
		myTopLayout->addWidget(itsSecretKey,2,1,1,4,Wt::AlignMiddle);
		myTopLayout->addWidget(itsGenSecretKeyBtn,2,5,1,1,Wt::AlignTop);
	}
	{
		myTopLayout->addWidget(itsCancelBtn,3,1,1,1,Wt::AlignCenter|Wt::AlignMiddle);
		myTopLayout->addWidget(itsSaveBtn,3,4,1,1,Wt::AlignCenter|Wt::AlignMiddle);
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

const IStrEdit& WtYubikoOtpKeyView::getPublicId() const {
	return *itsPublicId;
}

IStrEdit& WtYubikoOtpKeyView::getPublicId() {
	return *itsPublicId;
}

IStrEdit& WtYubikoOtpKeyView::getPublicIdLen() {
	return *itsPublicIdLen;
}

const IStrEdit& WtYubikoOtpKeyView::getPublicIdLen() const {
	return *itsPublicIdLen;
}

const IStrEdit& WtYubikoOtpKeyView::getPrivateId() const {
	return *itsPrivateId;
}

IStrEdit& WtYubikoOtpKeyView::getPrivateId() {
	return *itsPrivateId;
}

const IStrEdit& WtYubikoOtpKeyView::getSecretKey() const {
	return *itsSecretKey;
}

IStrEdit& WtYubikoOtpKeyView::getSecretKey() {
	return *itsSecretKey;
}

const IButton& WtYubikoOtpKeyView::getGenPublicIdentityBtn() const {
	return *itsGenPublicIdentityBtn;
}

IButton& WtYubikoOtpKeyView::getGenPublicIdentityBtn() {
	return *itsGenPublicIdentityBtn;
}

const IButton& WtYubikoOtpKeyView::getGenPrivateIdentityBtn() const {
	return *itsGenPrivateIdentityBtn;
}

IButton& WtYubikoOtpKeyView::getGenPrivateIdentityBtn() {
	return *itsGenPrivateIdentityBtn;
}

const IButton& WtYubikoOtpKeyView::getGenSecretKeyBtn() const {
	return *itsGenSecretKeyBtn;
}

IButton& WtYubikoOtpKeyView::getGenSecretKeyBtn() {
	return *itsGenSecretKeyBtn;
}

const IButton& WtYubikoOtpKeyView::getCancelBtn() const {
	return *itsCancelBtn;
}

IButton& WtYubikoOtpKeyView::getCancelBtn() {
	return *itsCancelBtn;
}

const IButton& WtYubikoOtpKeyView::getSaveBtn() const {
	return *itsSaveBtn;
}

IButton& WtYubikoOtpKeyView::getSaveBtn() {
	return *itsSaveBtn;
}

void WtYubikoOtpKeyView::show() {
	itsDlg->show();
}

void WtYubikoOtpKeyView::finishedSlot(WDialog::DialogCode pCode) {
	getAcceptedSignal()(pCode == WDialog::DialogCode::Accepted);
}

} /* namespace trihlav */
