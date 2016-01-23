/*
 * trihlavWtKeyListView.cpp
 *
 *  Created on: 23.01.2016
 *      Author: grobap
 */

#include <Wt/WTable>
#include <Wt/WText>
#include "trihlavWtKeyListView.hpp"

namespace trihlav {

WtKeyListView::WtKeyListView() {
	// TODO Auto-generated constructor stub
	itsTable = new Wt::WTable();
	itsTable->setHeaderCount(1);
	itsTable->setWidth(Wt::WLength("100%"));

	itsTable->elementAt(0, 0)->addWidget(new Wt::WText("#"));
	itsTable->elementAt(0, 1)->addWidget(new Wt::WText("Public ID"));
	itsTable->elementAt(0, 2)->addWidget(new Wt::WText("Type"));
	itsTable->elementAt(0, 3)->addWidget(new Wt::WText("Note"));

}

WtKeyListView::~WtKeyListView() {
	// TODO Auto-generated destructor stub
}

Wt::WWidget* WtKeyListView::getWWidget() {
	return itsTable;
}

void WtKeyListView::setupUi() {
}

} /* namespace trihlav */
