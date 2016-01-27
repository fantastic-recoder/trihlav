/*
 * trihlavWtKeyListView.cpp
 *
 *  Created on: 23.01.2016
 *      Author: grobap
 */

#include <Wt/WTable>
#include <Wt/WPushButton>
#include <Wt/WContainerWidget>
#include "trihlavWtPushButton.hpp"
#include "trihlavWtKeyListView.hpp"

using namespace Wt;

namespace trihlav {

WtKeyListView::WtKeyListView() {
	itsPanel = new WContainerWidget;
	itsBtnAdd = new WtPushButton("New key");
	itsTable = new WTable();
	itsTable->setHeaderCount(1);
	itsTable->setWidth(Wt::WLength("100%"));

	itsTable->elementAt(0, 0)->addWidget(new Wt::WText("#"));
	itsTable->elementAt(0, 1)->addWidget(new Wt::WText("Public ID"));
	itsTable->elementAt(0, 2)->addWidget(new Wt::WText("Type"));
	itsTable->elementAt(0, 3)->addWidget(new Wt::WText("Note"));

	itsPanel->addWidget(itsBtnAdd);
	itsPanel->addWidget(itsTable);
}

WtKeyListView::~WtKeyListView() {
	// TODO Auto-generated destructor stub
}

Wt::WWidget* WtKeyListView::getWWidget() {
	return itsPanel;
}

IButton& WtKeyListView::getBtnAddKey() {
	return *itsBtnAdd;
}

} /* namespace trihlav */
