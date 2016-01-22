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
#include "trihlavWtPswdChckView.hpp"
#include "trihlavLib/trihlavCannotCastImplementation.hpp"

using namespace Wt;
using namespace std;

namespace trihlav {

/**
 * 	Create a itsNavigation bar with a link to a web page.
 *
 */
void WtMainPanelView::setupUi() {
	// Create a itsNavigation bar with a link to a web page.
	itsNavigation = new Wt::WNavigationBar(itsView);
	itsNavigation->setTitle("Trihlav OTP Server",
			"http://www.google.com/search?q=One+Time+Password");
	itsNavigation->setResponsive(true);
	Wt::WStackedWidget* contentsStack = new Wt::WStackedWidget(itsView);
	contentsStack->addStyleClass("contents");
	// Setup a Left-aligned menu.
	setLeftMenu(new Wt::WMenu(contentsStack, itsView));
	itsNavigation->addMenu(getLeftMenu());
	Wt::WText* searchResult = new Wt::WText("Buy or Sell... Bye!");
	getLeftMenu()->addItem("Home", new Wt::WText("There is no safer place 4 Your data!"));
	getLeftMenu()->addItem("Layout", new Wt::WText("Layout contents"))->setLink(
			Wt::WLink(Wt::WLink::InternalPath, "/layout"));
	getLeftMenu()->addItem("Sales", searchResult);
	// Setup a Right-aligned menu.
	Wt::WMenu* rightMenu = new Wt::WMenu();
	itsNavigation->addMenu(rightMenu, Wt::AlignRight);
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
				getLeftMenu()->select(2); // is the index of the "Sales"
					searchResult->setText(Wt::WString("Nothing found for {1}.").arg(edit->text()));
				}));
	itsNavigation->addSearch(edit, Wt::AlignRight);
	itsView->addWidget(contentsStack);
}

void WtMainPanelView::add(const string& pName, IPswdChckView& pPswdChckView) {
	WtPswdChckView* myPswdChckView=dynamic_cast<WtPswdChckView*>(&pPswdChckView);
	if(myPswdChckView==0) {
		//TODO add rtti of the base type to the err msg
		throw new CannotCastImplementation("WtPswdChckView");
	}
	getLeftMenu()->addItem(pName.c_str(), myPswdChckView->getWWidget());
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
