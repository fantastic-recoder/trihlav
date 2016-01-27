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

#ifndef TRIHLAV_WT_KEY_LIST_VIEW_HPP_
#define TRIHLAV_WT_KEY_LIST_VIEW_HPP_

#include "trihlavLib/trihlavIKeyListView.hpp"
#include "trihlavIWtView.hpp"

namespace Wt {

class WWidget;
class WTable;
class WContainerWidget;

}  // namespace Wt

namespace trihlav {

class WtPushButton;

class WtKeyListView: virtual public IKeyListView, virtual public IWtView {
public:
	WtKeyListView();
	virtual ~WtKeyListView();
	virtual Wt::WWidget* getWWidget();

	const Wt::WTable* getTable() const {
		return itsTable;
	}

	Wt::WTable* getTable() {
		return itsTable;
	}

	virtual IButton&  getBtnAddKey();

protected:
	void setTable(Wt::WTable* myTable) {
		itsTable = myTable;
	}

private:
	Wt::WTable *itsTable;
	WtPushButton* itsBtnAdd;
	Wt::WContainerWidget* itsPanel;
};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_KEY_LIST_VIEW_HPP_ */
