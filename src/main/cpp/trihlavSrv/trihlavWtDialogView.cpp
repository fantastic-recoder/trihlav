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
#include <Wt/WPushButton>
#include <Wt/WHBoxLayout>

#include "trihlavLib/trihlavLogApi.hpp"
#include "trihlavWtDialogView.hpp"
#include "trihlavWtPushButton.hpp"

using Wt::WDialog;
using Wt::WLength;
using Wt::WHBoxLayout;
using std::string;
using boost::locale::translate;
using U = Wt::WLength::Unit;

namespace trihlav {
WtDialogView::WtDialogView() : //
		m_Dlg(new WDialog), //
		m_CancelBtn(new WtPushButton(translate("Cancel"))), //
		m_OkBtn(new WtPushButton(translate("ok"))) //

{
	BOOST_LOG_NAMED_SCOPE("WtDialogView::WtDialogView()");
	WHBoxLayout* myBtnLayout = new WHBoxLayout;
	{
		m_CancelBtn->resize(WLength(11.0, U::FontEm), WLength(4.0, U::FontEm));
		m_OkBtn->resize(WLength(11.0, U::FontEm), WLength(4.0, U::FontEm));
		myBtnLayout->addWidget(m_OkBtn);
		myBtnLayout->addWidget(m_CancelBtn);
	}
	m_Dlg->footer()->setLayout(myBtnLayout);
	m_Dlg->finished().connect(this, &WtDialogView::finishedSlot);
	m_CancelBtn->clicked().connect(m_Dlg.get(), &WDialog::reject);
	m_OkBtn->clicked().connect(m_Dlg.get(), &WDialog::accept);
}

const ButtonIface& WtDialogView::getBtnCancel() const {
	return *m_CancelBtn;
}

ButtonIface& WtDialogView::getBtnCancel() {
	return *m_CancelBtn;
}

const ButtonIface& WtDialogView::getBtnOk() const {
	return *m_OkBtn;
}

ButtonIface& WtDialogView::getBtnOk() {
	return *m_OkBtn;
}

void WtDialogView::show() {
	m_Dlg->show();
}

WtDialogView::~WtDialogView() {
	BOOST_LOG_NAMED_SCOPE("WtDialogView::~WtDialogView");
}

void WtDialogView::finishedSlot(WDialog::DialogCode pCode) {
	sigDialogFinished(pCode == WDialog::DialogCode::Accepted);
	m_Dlg->hide();
}

Wt::WDialog &WtDialogView::getDlg() {
	return *m_Dlg;
}
}
