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
#include <Wt/WPanel>
#include <Wt/WWidget>
#include <Wt/WText>
#include <Wt/WLength>
#include <Wt/WLineEdit>
#include <Wt/WContainerWidget>

#include <boost/locale.hpp>

#include "trihlavWtPswdChckView.hpp"
#include "trihlavWtStrEdit.hpp"
#include "trihlavWtPushButton.hpp"

using Wt::WContainerWidget;
using Wt::WText;
using Wt::WWidget;
using Wt::WLength;
using boost::locale::translate;

namespace trihlav {

WtPswdChckView::WtPswdChckView() //
:m_BtnOk(new WtPushButton(translate("check")))
,m_EdtPswd(new WtStrEdit)
{
	m_BtnOk->setWidth(WLength(7.0,WLength::FontEm));
	m_EdtPswd->setWidth(WLength(32.0,WLength::FontEm));
	m_EdtPswd->setMargin(WLength(16.0,WLength::Pixel));
	m_MainPanel = new WContainerWidget();
	m_MainPanel->setWidth(WLength(100.0,WLength::Percentage));
	m_MainPanel->setHeight(WLength(7.0,WLength::FontEm));
	m_MainPanel->setContentAlignment(Wt::AlignCenter|Wt::AlignBottom);
	m_MainPanel->addWidget(new WText(translate("One time password").str()));
	m_MainPanel->addWidget(m_EdtPswd);
	m_MainPanel->addWidget(m_BtnOk);
}

WtPswdChckView::~WtPswdChckView() {
	// TODO Auto-generated destructor stub
}

WWidget* WtPswdChckView::getWWidget() {
	return m_MainPanel;
}

void WtPswdChckView::setupUi() {
}

ButtonIface& WtPswdChckView::getBtnOk() {
	return *m_BtnOk;
}

StrEditIface& WtPswdChckView::getEdtPswd0() {
	return *m_EdtPswd;
}

} /* namespace trihlav */

