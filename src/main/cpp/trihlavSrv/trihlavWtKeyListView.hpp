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

#include <Wt/WContainerWidget.h>

#include "trihlavLib/trihlavKeyListViewIface.hpp"
#include "trihlavWtViewIface.hpp"

namespace Wt {

class WWidget;
class WTableView;

}  // namespace Wt

namespace trihlav {

class WtPushButton;
class WtKeyListModel;

class WtKeyListView: virtual public KeyListViewIface, //
		virtual public WtViewIface, //
		virtual public Wt::WContainerWidget {
public:
	WtKeyListView();
	virtual ~WtKeyListView();

    virtual Wt::WWidget *getWWidget() override;

	const Wt::WTableView* getTable() const {
		return m_Table;
	}

	Wt::WTableView* getTable() {
		return m_Table;
	}

	virtual ButtonIface& getBtnAddKey() override;
	virtual ButtonIface& getBtnDelKey() override;
	virtual ButtonIface& getBtnReload() override;
	virtual ButtonIface& getBtnEditKey() override;
	virtual void clear() override;
	virtual void addRow(const KeyRow_t& pRow) override;
	virtual void addedAllRows() override;
	virtual void unselectAll() override;
	virtual const KeyRow_t& getRow(int pId) const override;

protected:
	virtual int getSelected();
	virtual void layoutSizeChanged(int, int) override;

	void setTable(Wt::WTableView* pTable) {
		m_Table = pTable;
	}

	void selectionChanged();

private:
	void createTable();

	Wt::WTableView *m_Table;
	WtPushButton* m_BtnAdd;
	WtPushButton* m_BtnDel;
	WtPushButton* m_BtnEdit;
	WtPushButton* m_BtnReload;
    std::shared_ptr<WtKeyListModel> m_DtaMdl;
	static const int K_TBL_V_MARGIN;
};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_KEY_LIST_VIEW_HPP_ */
