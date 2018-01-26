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

#include <string>
#include <array>
#include <list>
#include <boost/locale.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include <Wt/WAny.h>
#include <Wt/WTableView.h>
#include <Wt/WPushButton.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WAbstractItemModel.h>

#include "trihlavWtPushButton.hpp"
#include "trihlavWtKeyListView.hpp"
#include "trihlavWtListModel.hpp"

using std::string;
using std::array;
using std::list;
using std::vector;
using boost::locale::translate;
using Wt::cpp17::any;
using Wt::WText;
using Wt::WContainerWidget;
using Wt::WHBoxLayout;
using Wt::WVBoxLayout;
using Wt::WLength;
using Wt::LengthUnit;
using Wt::WTableView;
using Wt::WAbstractTableModel;
using Wt::WModelIndex;
using Wt::Orientation;
using Wt::ItemDataRole;
using Wt::WModelIndexSet;
using Wt::WLayout;
using std::vector;
using U = Wt::WLength::Unit;


namespace trihlav {

const int WtKeyListView::K_TBL_V_MARGIN = 12;

/**
 * @brief The WtKeyListModel class holds the data supplyed by the presenter.
 */
class WtKeyListModel: public WtListModel<int, std::string, std::string,
		std::string, int, int> {
public:
	WtKeyListModel() :
			WtListModel<int, std::string, std::string, std::string, int, int>(
					{ { translate("Record ID") }, { translate("Public ID") }, {
							translate("Description") }, { translate(
							"Private ID") }, { translate("Use counter") }, {
							translate("Counter") } }) {
	}
}
;

void WtKeyListView::layoutSizeChanged(int pW, int pH) {
	BOOST_LOG_TRIVIAL(debug)<< "W=" << pW <<" H=" << pH;
	const int WIDTH = 120; const int K_TBL_W=pW-2*K_TBL_V_MARGIN;
	int K_COL_CNT {1};
	if(m_Table->model()) {
		K_COL_CNT=m_Table->model()->columnCount();
	}
	const int K_TBL_INT_M=7*K_COL_CNT+2;
	for (int i = 0; i < K_COL_CNT; ++i) {
		if(i==2) {
			m_Table->setColumnWidth(i,K_TBL_W-5*WIDTH-K_TBL_INT_M);
		} else {
			m_Table->setColumnWidth(i, 120);
		}
	}
	m_Table->resize(WLength(pW, U::Pixel), WLength(pH, U::Pixel));
}

void WtKeyListView::createTable() {
	m_Table = new WTableView();
	m_Table->setModel(m_DtaMdl);
	m_Table->setAlternatingRowColors(true);
	m_Table->setCanReceiveFocus(true);
	m_Table->setColumnResizeEnabled(true);
	m_Table->setColumnWidth(2, "400px");
    m_Table->setSelectionMode(Wt::SelectionMode::Single);
	m_Table->resize(WLength(100.0, U::Percentage), WLength(128.0, U::FontEm));
	m_Table->selectionChanged().connect(this,
			&WtKeyListView::selectionChanged);
}

WtKeyListView::WtKeyListView() {
    m_DtaMdl = std::shared_ptr<WtKeyListModel>(new WtKeyListModel);
	WHBoxLayout* myBtnsLayout = new WHBoxLayout;
	WVBoxLayout* myTopLayout = new WVBoxLayout;
	m_BtnAdd = new WtPushButton(translate("New key").str());
	m_BtnDel = new WtPushButton(translate("Delete key").str());
	m_BtnReload = new WtPushButton(translate("Reload keys").str());
	m_BtnEdit = new WtPushButton(translate("Edit key").str());
    m_BtnAdd->setWidth(WLength {6, LengthUnit::FontEm});
    m_BtnEdit->setWidth(WLength {6, LengthUnit::FontEm});
    m_BtnDel->setWidth(WLength {6, LengthUnit::FontEm});
    m_BtnReload->setWidth(WLength {6, LengthUnit::FontEm});
    myBtnsLayout->addWidget(std::unique_ptr<WWidget>(m_BtnAdd));
    myBtnsLayout->addWidget(std::unique_ptr<WWidget>(m_BtnEdit));
    myBtnsLayout->addWidget(std::unique_ptr<WWidget>(m_BtnDel));
    myBtnsLayout->addWidget(std::unique_ptr<WWidget>(m_BtnReload));
	createTable();
    myTopLayout->addLayout(std::unique_ptr<Wt::WLayout>(myBtnsLayout));
    myTopLayout->addWidget(std::unique_ptr<Wt::WWidget>(m_Table));
	myTopLayout->setContentsMargins(K_TBL_V_MARGIN, K_TBL_V_MARGIN,
			K_TBL_V_MARGIN, K_TBL_V_MARGIN);
	myTopLayout->setSpacing(K_TBL_V_MARGIN);
    setLayout(std::unique_ptr<WLayout>(myTopLayout));
	setLayoutSizeAware(true);
}

WtKeyListView::~WtKeyListView() {
}

Wt::WWidget* WtKeyListView::getWWidget() {
	return this;
}

ButtonIface& WtKeyListView::getBtnAddKey() {
	return *m_BtnAdd;
}

ButtonIface& WtKeyListView::getBtnEditKey() {
	return *m_BtnEdit;
}

ButtonIface& trihlav::WtKeyListView::getBtnDelKey() {
	return *m_BtnDel;
}

ButtonIface& trihlav::WtKeyListView::getBtnReload() {
	return *m_BtnReload;
}

void WtKeyListView::clear() {
	m_Table->clearSelection();
	m_DtaMdl->clear();
}

void WtKeyListView::addRow(const KeyRow_t& pRow) {
	m_DtaMdl->addRow(pRow);
}

void WtKeyListView::addedAllRows() {
	BOOST_LOG_TRIVIAL(debug)<< "We have " << m_DtaMdl->rowCount();
	m_Table->refresh();
}

void WtKeyListView::unselectAll() {
	m_Table->clearSelection();
	this->selectionChangedSig(-1);
}

/**
 * @return a list of ids of the selected keys.
 */
int WtKeyListView::getSelected() {
	WModelIndexSet mySelected { m_Table->selectedIndexes() };
	if (mySelected.empty()) {
		return -1;
	}
	return mySelected.begin()->row();
}

const WtKeyListView::KeyRow_t& WtKeyListView::getRow(int pId) const {
	return m_DtaMdl->getRow(pId);
}

void WtKeyListView::selectionChanged() {
	BOOST_LOG_NAMED_SCOPE("WtKeyListView::selectionChanged");
	this->selectionChangedSig(getSelected());
}

} /* namespace trihlav */
