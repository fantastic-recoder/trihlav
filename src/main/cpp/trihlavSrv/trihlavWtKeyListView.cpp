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
	WHBoxLayout* myBtnsLayout = new WHBoxLayout;
	WVBoxLayout* myTopLayout = new WVBoxLayout;
	itsBtnAdd = new WtPushButton("New key");
	itsBtnDel = new WtPushButton("Delete key");
	itsBtnReload = new WtPushButton("Reload keys");
	itsBtnEdit = new WtPushButton("Edit key");
	itsBtnAdd->setWidth(WLength { 6, WLength::FontEm });
	itsBtnEdit->setWidth(WLength { 6, WLength::FontEm });
	itsBtnDel->setWidth(WLength { 6, WLength::FontEm });
	itsBtnReload->setWidth(WLength { 6, WLength::FontEm });
	myBtnsLayout->addWidget(itsBtnAdd);
	myBtnsLayout->addWidget(itsBtnEdit);
	myBtnsLayout->addWidget(itsBtnDel);
	myBtnsLayout->addWidget(itsBtnReload);
	itsTable = new WTable();
	itsTable->setHeaderCount(1);
	itsTable->addStyleClass("table-hover");
	itsTable->addStyleClass("table-striped");
	itsTable->setWidth(Wt::WLength("100%"));
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

IButton& WtKeyListView::getBtnEditKey() {
	return *itsBtnEdit;
}

IButton& trihlav::WtKeyListView::getBtnDelKey() {
	return *itsBtnDel;
}

IButton& trihlav::WtKeyListView::getBtnReload() {
	return *itsBtnReload;
}

void WtKeyListView::clear() {
	itsRowCounter = 0;
	itsTable->clear();
	addTableHeader();
}

void WtKeyListView::addRow(const KeyListRow_t pRow) {
	itsRowCounter++;
	auto myId = new Wt::WText(boost::lexical_cast<std::string>(pRow.get<0>()));
	myId->setTextAlignment(AlignCenter);
	auto myDesc = new Wt::WText(pRow.get<1>());
	myDesc->setTextAlignment(AlignCenter);
	itsTable->elementAt(itsRowCounter, 0)->addWidget(myId);
	itsTable->elementAt(itsRowCounter, 1)->addWidget(myDesc);
	itsTable->elementAt(itsRowCounter, 2)->addWidget(
			new Wt::WText(pRow.get<2>()));
	itsTable->elementAt(itsRowCounter, 3)->addWidget(
			new Wt::WText(pRow.get<3>()));
}

void WtKeyListView::addedAllRows() {
}
} /* namespace trihlav */
