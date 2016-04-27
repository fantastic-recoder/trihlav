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
#ifndef TRIHLAV_MOCK_KEY_LIST_VIEW_HPP_
#define TRIHLAV_MOCK_KEY_LIST_VIEW_HPP_

#include <gmock/gmock.h>
#include "trihlavLib/trihlavKeyListViewIface.hpp"

#include "trihlavMockButton.hpp"

namespace trihlav {

struct MockKeyListView: virtual KeyListViewIface {
	MockButton itsMockBtnAddKey;
	MockButton itsMockBtnEditKey;
	MockButton itsMockBtnReloadKey;
	MockButton itsMockBtnDelKey;
	MockKeyListView();//
	MOCK_METHOD0(getBtnAddKey, ButtonIface& ());//
	MOCK_METHOD0(getBtnDelKey, ButtonIface& ());//
	MOCK_METHOD0(getBtnEditKey, ButtonIface& ());//
	MOCK_METHOD0(getBtnReload,ButtonIface& ());//
	MOCK_METHOD0(unselectAll,void ());//
	MOCK_METHOD0(clear,void ());//
	MOCK_METHOD1(addRow,void (const KeyListRow_t pRow));//
	MOCK_METHOD0(addedAllRows,void ());//
};

}
/* namespace trihlav */

#endif /* TRIHLAV_MOCK_KEY_LIST_VIEW_HPP_ */
