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
:itsBtnOk(new WtPushButton(translate("check")))
,itsEdtPswd(new WtStrEdit)
{
	itsBtnOk->setWidth(WLength(7.0,WLength::FontEm));
	itsEdtPswd->setWidth(WLength(32.0,WLength::FontEm));
	itsEdtPswd->setMargin(WLength(16.0,WLength::Pixel));
	itsMainPanel = new WContainerWidget();
	itsMainPanel->setWidth(WLength(100.0,WLength::Percentage));
	itsMainPanel->setHeight(WLength(7.0,WLength::FontEm));
	itsMainPanel->setContentAlignment(Wt::AlignCenter|Wt::AlignBottom);
	itsMainPanel->addWidget(new WText(translate("One time password").str()));
	itsMainPanel->addWidget(itsEdtPswd);
	itsMainPanel->addWidget(itsBtnOk);
}

WtPswdChckView::~WtPswdChckView() {
	// TODO Auto-generated destructor stub
}

WWidget* WtPswdChckView::getWWidget() {
	return itsMainPanel;
}

void WtPswdChckView::setupUi() {
}

ButtonIface& WtPswdChckView::getBtnOk() {
	return *itsBtnOk;
}

StrEditIface& WtPswdChckView::getEdtPswd0() {
	return *itsEdtPswd;
}

} /* namespace trihlav */

