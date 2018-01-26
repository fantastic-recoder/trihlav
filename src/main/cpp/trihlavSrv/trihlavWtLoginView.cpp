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

#include <Wt/WGridLayout.h>

#include "trihlavWtLoginView.hpp"
#include "trihlavWtStrEdit.hpp"
#include "trihlavWtLabel.hpp"

using std::unique_ptr;
using Wt::WWidget;
using Wt::WLayout;
using Wt::WGridLayout;
using Wt::AlignmentFlag;
using U = Wt::WLength::Unit;
using Wt::WLength;

namespace trihlav {

WtLoginView::WtLoginView() //
:
		m_EdtUserName(new WtStrEdit)  //
				, m_EdtPassword(new WtStrEdit) //
				, m_LblUserName(new WtLabel("User name")) //
				, m_LblPassword(new WtLabel("Password")) //
{
	getDlg().setWidth(WLength(32, U::FontEm));
	WGridLayout* myTopLayout = new WGridLayout;
	{
		m_LblUserName->setWidth(WLength(9.0,U::FontEm));
        myTopLayout->addWidget(unique_ptr<WWidget>(m_LblUserName), 0, 0, 1, 1,
                               AlignmentFlag::Right | AlignmentFlag::Middle);
        myTopLayout->addWidget(unique_ptr<WWidget>(m_EdtUserName), 0, 1, 1, 1, AlignmentFlag::Middle);
	}
	{
		m_LblPassword->setWidth(WLength(9.0,U::FontEm));
        myTopLayout->addWidget(unique_ptr<WWidget>(m_LblPassword), 2, 0, 1, 1,
                               AlignmentFlag::Right | AlignmentFlag::Middle);
        myTopLayout->addWidget(unique_ptr<WWidget>(m_EdtPassword), 2, 1, 1, 1, AlignmentFlag::Middle);
    }
    getDlg().contents()->setLayout(unique_ptr<WLayout>(myTopLayout));
}

StrEditIface& WtLoginView::getEdtUserName() {
	return *m_EdtUserName;
}

StrEditIface& WtLoginView::getEdtPassword() {
	return *m_EdtPassword;
}

LabelIface& WtLoginView::getLblUserName() {
	return *m_LblUserName;
}

LabelIface& WtLoginView::getLblPassword() {
	return *m_LblPassword;
}

} /* namespace trihlav */

