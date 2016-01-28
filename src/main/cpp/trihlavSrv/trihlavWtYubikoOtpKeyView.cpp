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

#include <Wt/WDialog>

#include "trihlavWtStrEdit.hpp"
#include "trihlavWtPushButton.hpp"
#include "trihlavWtYubikoOtpKeyView.hpp"

using namespace Wt;
using namespace std;
using namespace boost;
using boost::locale::translate;

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
	itsDlg->contents()->addWidget(itsPublicId);
	itsDlg->contents()->addWidget(itsPublicIdLen);
	itsDlg->contents()->addWidget(itsPrivateId);
	itsDlg->contents()->addWidget(itsSecretKey);
	itsDlg->contents()->addWidget(itsGenPublicIdentityBtn);
	itsDlg->contents()->addWidget(itsGenPrivateIdentityBtn);
	itsDlg->contents()->addWidget(itsCancelBtn);
	itsDlg->contents()->addWidget(itsSaveBtn);
    itsDlg->finished().connect(this,&WtYubikoOtpKeyView::finishedSlot);
    itsCancelBtn->clicked().connect(itsDlg.get(),&WDialog::reject);
    itsSaveBtn->clicked().connect(itsDlg.get(),&WDialog::accept);
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

void WtYubikoOtpKeyView::finishedSlot(WDialog::DialogCode pCode)
{
    getAcceptedSignal()(pCode==WDialog::DialogCode::Accepted);
}

} /* namespace trihlav */
