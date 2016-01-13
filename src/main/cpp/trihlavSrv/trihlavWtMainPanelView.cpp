/*
 * trihlavWtMainPanelView.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WMessageBox>
#include <Wt/WNavigationBar>
#include <Wt/WPopupMenu>
#include <Wt/WPopupMenuItem>
#include <Wt/WStackedWidget>
#include <Wt/WText>
#include <Wt/WContainerWidget>

#include "trihlavWtMainPanelView.hpp"

using namespace Wt;

namespace trihlav {

/**
 * 	Create a navigation bar with a link to a web page.
 *
 */
void WtMainPanelView::setupUi() {
	itsView->setWidth(WLength(1200.0,WLength::Pixel));
	itsView->setHeight(WLength(800.0,WLength::Pixel));
	// Create a navigation bar with a link to a web page.
	Wt::WNavigationBar* navigation = new Wt::WNavigationBar(itsView);
	navigation->setTitle("Res Diums Safe",
			"http://www.google.com/search?q=Res+Dium");
	navigation->setResponsive(true);
	Wt::WStackedWidget* contentsStack = new Wt::WStackedWidget(itsView);
	contentsStack->addStyleClass("contents");
	// Setup a Left-aligned menu.
	Wt::WMenu* leftMenu = new Wt::WMenu(contentsStack, itsView);
	navigation->addMenu(leftMenu);
	Wt::WText* searchResult = new Wt::WText("Buy or Sell... Bye!");
	leftMenu->addItem("Home", new Wt::WText("There is no better place!"));
	leftMenu->addItem("Layout", new Wt::WText("Layout contents"))->setLink(
			Wt::WLink(Wt::WLink::InternalPath, "/layout"));
	leftMenu->addItem("Sales", searchResult);
	// Setup a Right-aligned menu.
	Wt::WMenu* rightMenu = new Wt::WMenu();
	navigation->addMenu(rightMenu, Wt::AlignRight);
	// Create a popup submenu for the Help menu.
	Wt::WPopupMenu* popup = new Wt::WPopupMenu();
	popup->addItem("Contents");
	popup->addItem("Index");
	popup->addSeparator();
	popup->addItem("About");
	popup->itemSelected().connect(
			std::bind(
					[=](Wt::WMenuItem* item) {
						Wt::WMessageBox* messageBox = new Wt::WMessageBox("Help", Wt::WString::fromUTF8("<p>Showing Help: {1}</p>").arg(item->text()), Wt::Information, Wt::Ok);
						messageBox->buttonClicked().connect(std::bind([=]() {
											delete messageBox;
										}
								));
						messageBox->show();
					}, std::placeholders::_1));
	Wt::WMenuItem* item = new Wt::WMenuItem("Help");
	item->setMenu(popup);
	rightMenu->addItem(item);
	// Add a Search control.
	Wt::WLineEdit* edit = new Wt::WLineEdit();
	edit->setEmptyText("Enter a search item");
	edit->enterPressed().connect(
			std::bind([=]() {
				leftMenu->select(2); // is the index of the "Sales"
					searchResult->setText(Wt::WString("Nothing found for {1}.").arg(edit->text()));
				}));
	navigation->addSearch(edit, Wt::AlignRight);
	itsView->addWidget(contentsStack);
}

WtMainPanelView::WtMainPanelView() {
	itsView = new WContainerWidget();
}

WtMainPanelView::~WtMainPanelView() {
	delete itsView;
}

WContainerWidget* WtMainPanelView::getNativeView() {
	return itsView;
}

} /* namespace trihlav */
