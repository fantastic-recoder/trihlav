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
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavMockButton.hpp"
#include "trihlavMockKeyListView.hpp"

using ::testing::Return;
using ::testing::ReturnRef;

namespace trihlav {

MockKeyListView::MockKeyListView() {
	BOOST_LOG_NAMED_SCOPE("MockKeyListView::MockKeyListView");

	ON_CALL(*this,getBtnAddKey()) //
	.WillByDefault(ReturnRef(m_MockBtnAddKey));
	ON_CALL(*this,getBtnDelKey()) //
	.WillByDefault(ReturnRef(m_MockBtnDelKey));
	ON_CALL(*this,getBtnEditKey()) //
	.WillByDefault(ReturnRef(m_MockBtnEditKey));
	ON_CALL(*this,getBtnReload()) //
	.WillByDefault(ReturnRef(m_MockBtnReloadKey));

}

} /* namespace trihlav */

