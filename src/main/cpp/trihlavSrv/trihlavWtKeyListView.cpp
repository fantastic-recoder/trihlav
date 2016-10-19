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

#include <Wt/WTableView>
#include <Wt/WPushButton>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include "trihlavWtPushButton.hpp"
#include "trihlavWtKeyListView.hpp"
#include "trihlavWtListModel.hpp"

using std::string;
using std::array;
using std::list;
using std::vector;
using boost::locale::translate;
using boost::any;
using Wt::WText;
using Wt::WContainerWidget;
using Wt::WHBoxLayout;
using Wt::WVBoxLayout;
using Wt::WLength;
using Wt::WTableView;
using Wt::WAbstractTableModel;
using Wt::WModelIndex;
using Wt::Orientation;
using Wt::DisplayRole;
using Wt::WModelIndexSet;
using std::vector;

namespace trihlav {

const int WtKeyListView::K_TBL_V_MARGIN = 12;

/**
 * @brief The WtKeyListModel class holds the data supplyed by the presenter.
 */
class WtKeyListModel: public WtListModel<int, std::string, std::string,
		std::string, int, int> {
public:
	WtKeyListModel() :
			WtListModel<int, std::string, std::string, std::string, int, int>( {
					{ translate("Record ID") }, { translate("Public ID") }, {
							translate("Description") }, { translate(
							"Private ID") }, { translate("Use counter") }, {
							translate("Counter") } }) {
	}
}
;

void WtKeyListView::layoutSizeChanged(int pW, int pH) {
	BOOST_LOG_TRIVIAL(debug)<< "W=" << pW <<" H=" << pH;
	const int WIDTH = 120; const int K_TBL_W=pW-2*K_TBL_V_MARGIN;
	const int K_COL_CNT=itsTable->model()->columnCount();
	const int K_TBL_INT_M=7*K_COL_CNT+2;
	for (int i = 0; i < K_COL_CNT; ++i) {
		if(i==2) {
			itsTable->setColumnWidth(i,K_TBL_W-5*WIDTH-K_TBL_INT_M);
		} else {
			itsTable->setColumnWidth(i, 120);
		}
	}
}

WtKeyListView::WtKeyListView() {
	itsDtaMdl = new WtKeyListModel;
	WHBoxLayout* myBtnsLayout = new WHBoxLayout;
	WVBoxLayout* myTopLayout = new WVBoxLayout;
	itsBtnAdd = new WtPushButton(translate("New key").str());
	itsBtnDel = new WtPushButton(translate("Delete key").str());
	itsBtnReload = new WtPushButton(translate("Reload keys").str());
	itsBtnEdit = new WtPushButton(translate("Edit key").str());
	itsBtnAdd->setWidth(WLength { 6, WLength::FontEm });
	itsBtnEdit->setWidth(WLength { 6, WLength::FontEm });
	itsBtnDel->setWidth(WLength { 6, WLength::FontEm });
	itsBtnReload->setWidth(WLength { 6, WLength::FontEm });
	myBtnsLayout->addWidget(itsBtnAdd);
	myBtnsLayout->addWidget(itsBtnEdit);
	myBtnsLayout->addWidget(itsBtnDel);
	myBtnsLayout->addWidget(itsBtnReload);
	itsTable = new WTableView();
	itsTable->setModel(itsDtaMdl);
	itsTable->setAlternatingRowColors(true);
	itsTable->setCanReceiveFocus(true);
	itsTable->setColumnResizeEnabled(true);
	itsTable->setColumnWidth(2, "400px");
	itsTable->setSelectionMode(Wt::SingleSelection);
	myTopLayout->addLayout(myBtnsLayout);
	myTopLayout->addWidget(itsTable);
	myTopLayout->setContentsMargins(K_TBL_V_MARGIN, K_TBL_V_MARGIN,
			K_TBL_V_MARGIN, K_TBL_V_MARGIN);
	myTopLayout->setSpacing(K_TBL_V_MARGIN);
	setLayout(myTopLayout);
	setLayoutSizeAware(true);
	itsTable->selectionChanged().connect(this,
			&WtKeyListView::selectionChanged);
}

WtKeyListView::~WtKeyListView() {
}

Wt::WWidget* WtKeyListView::getWWidget() {
	return this;
}

ButtonIface& WtKeyListView::getBtnAddKey() {
	return *itsBtnAdd;
}

ButtonIface& WtKeyListView::getBtnEditKey() {
	return *itsBtnEdit;
}

ButtonIface& trihlav::WtKeyListView::getBtnDelKey() {
	return *itsBtnDel;
}

ButtonIface& trihlav::WtKeyListView::getBtnReload() {
	return *itsBtnReload;
}

void WtKeyListView::clear() {
	itsDtaMdl->clear();
}

void WtKeyListView::addRow(const KeyRow_t& pRow) {
	itsDtaMdl->addRow(pRow);
}

void WtKeyListView::addedAllRows() {
	BOOST_LOG_TRIVIAL(debug)<< "We have " << itsDtaMdl->rowCount();
	itsTable->setModel(itsDtaMdl);
}

void WtKeyListView::unselectAll() {
	itsTable->clearSelection();
	this->selectionChangedSig(-1);
}

/**
 * @return a list of ids of the selected keys.
 */
int WtKeyListView::getSelected() {
	WModelIndexSet mySelected { itsTable->selectedIndexes() };
	if (mySelected.empty()) {
		return -1;
	}
	return mySelected.begin()->row();
}

const WtKeyListView::KeyRow_t& WtKeyListView::getRow(int pId) const {
	return itsDtaMdl->getRow(pId);
}

void WtKeyListView::selectionChanged() {
	BOOST_LOG_NAMED_SCOPE("WtKeyListView::selectionChanged");
	this->selectionChangedSig(getSelected());
}

} /* namespace trihlav */
