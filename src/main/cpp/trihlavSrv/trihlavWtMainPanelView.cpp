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

#include "trihlavIWtView.hpp"
#include "trihlavWtMainPanelView.hpp"
#include "trihlavWtPswdChckView.hpp"
#include "trihlavWtKeyListView.hpp"
#include "trihlavLib/trihlavCannotCastImplementation.hpp"
#include "trihlavLib/trihlavVersion.hpp"

using namespace Wt;
using namespace std;

namespace trihlav {

/**
 * 	Create a itsNavigation bar with a link to a web page.
 *
 */
void WtMainPanelView::setupUi() {
	itsView->addWidget(getContentsStack());
}

void WtMainPanelView::add(const string& pName,IKeyListView&  pKeyListView){
	WtKeyListView* myKeyListView =
			dynamic_cast<WtKeyListView*>(&pKeyListView);
	if (myKeyListView== 0) {
		//TODO add rtti of the base type to the err msg
		throw new CannotCastImplementation("WtKeyListView");
	}
	addView(pName,*myKeyListView);
}

void WtMainPanelView::add(const string& pName, IPswdChckView& pPswdChckView) {
	WtPswdChckView* myPswdChckView =
			dynamic_cast<WtPswdChckView*>(&pPswdChckView);
	if (myPswdChckView == 0) {
		//TODO add rtti of the base type to the err msg
		throw new CannotCastImplementation("WtPswdChckView");
	}
	addView(pName,*myPswdChckView);
}

void WtMainPanelView::addView(const std::string& pName,IWtView&  pView) {
	WMenuItem* myItem = getLeftMenu()->addItem(pName.c_str(),
			pView.getWWidget());
	string myUrl("/"+pName);
	myItem->setLink(
			Wt::WLink(Wt::WLink::InternalPath, myUrl.c_str()));
}

WtMainPanelView::WtMainPanelView():itsView ( new WContainerWidget()) {
	// Create a itsNavigation bar with a link to a web page.
	setNavigation(new Wt::WNavigationBar(itsView));
	getNavigation()->setTitle("Trihlav OTP Server",
			"http://www.google.com/search?q=One+Time+Password");
	getNavigation()->setResponsive(true);
	setContentsStack (new Wt::WStackedWidget(itsView));
	itsContentsStack->addStyleClass("contents");
	// Setup a Left-aligned menu.
	setLeftMenu(new Wt::WMenu(itsContentsStack, itsView));
	getNavigation()->addMenu(getLeftMenu(), Wt::AlignLeft);
	// Setup a Right-aligned menu.
	Wt::WMenu* rightMenu = new Wt::WMenu();
	getNavigation()->addMenu(rightMenu, Wt::AlignRight);
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
				getLeftMenu()->select(1); // is the index of the "Sales"
					Wt::WMessageBox* messageBox = new Wt::WMessageBox("Help", Wt::WString::fromUTF8("<p>Not yet implemented, should search for: {1}</p>").arg(edit->valueText()), Wt::Information, Wt::Ok);
					messageBox->buttonClicked().connect(std::bind([=]() {
										delete messageBox;
									}
							));
					messageBox->show();
				}));
	getNavigation()->addSearch(edit, Wt::AlignRight);
}

WtMainPanelView::~WtMainPanelView() {
	delete itsView;
}

WContainerWidget* WtMainPanelView::getNativeView() {
	return itsView;
}

} /* namespace trihlav */
