/*
 * trihlavWtKeyListView.cpp
 *
 *  Created on: 23.01.2016
 *      Author: grobap
 */

#include <Wt/WTable>
#include <Wt/WPushButton>
#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include "trihlavWtPushButton.hpp"
#include "trihlavWtKeyListView.hpp"

using namespace Wt;

namespace trihlav {

void WtKeyListView::addTableHeader() {
	itsTable->elementAt(0, 0)->addWidget(new Wt::WText("#"));
	itsTable->elementAt(0, 1)->addWidget(new Wt::WText("Public ID"));
	itsTable->elementAt(0, 2)->addWidget(new Wt::WText("Description"));
	itsTable->elementAt(0, 3)->addWidget(new Wt::WText("Private ID"));
}

WtKeyListView::WtKeyListView() {
	itsPanel = new WContainerWidget;
	WHBoxLayout* myBtnsLayout= new WHBoxLayout;
	WVBoxLayout* myTopLayout= new WVBoxLayout;
	itsBtnAdd = new WtPushButton("New key");
	itsBtnDel = new WtPushButton("Delete key");
	itsBtnReload = new WtPushButton("Reload keys");
	myBtnsLayout->addWidget(itsBtnAdd,AlignLeft);
	myBtnsLayout->addWidget(itsBtnDel,AlignLeft);
	myBtnsLayout->addWidget(itsBtnReload,AlignRight);
	itsTable = new WTable();
	itsTable->setHeaderCount(1);
	itsTable->setWidth(Wt::WLength("100%"));

	addTableHeader();
	myTopLayout->addLayout(myBtnsLayout);
	myTopLayout->addWidget(itsTable);
	itsPanel->setLayout(myTopLayout);
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


IButton& trihlav::WtKeyListView::getBtnDelKey() {
	return *itsBtnDel;
}

IButton& trihlav::WtKeyListView::getBtnReload() {
	return *itsBtnReload;
}

void WtKeyListView::clear() {
	itsRowCounter=0;
	itsTable->clear();
	addTableHeader();
}

void WtKeyListView::addRow(const KeyListRow_t pRow) {
	itsRowCounter++;
	itsTable->elementAt(itsRowCounter,0)->addWidget(new Wt::WText(boost::lexical_cast<std::string>(pRow.get<0>())));
	itsTable->elementAt(itsRowCounter,1)->addWidget(new Wt::WText(pRow.get<1>()));
	itsTable->elementAt(itsRowCounter,2)->addWidget(new Wt::WText(pRow.get<2>()));
	itsTable->elementAt(itsRowCounter,3)->addWidget(new Wt::WText(pRow.get<3>()));
}

void WtKeyListView::addedAllRows() {
}
} /* namespace trihlav */
