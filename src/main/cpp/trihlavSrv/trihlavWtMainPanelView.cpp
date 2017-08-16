/*
 * trihlavWtMainPanelView.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include <string>
#include <boost/locale.hpp>

#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WMessageBox>
#include <Wt/WNavigationBar>
#include <Wt/WPopupMenu>
#include <Wt/WPopupMenuItem>
#include <Wt/WStackedWidget>
#include <Wt/WText>
#include <Wt/WContainerWidget>

#include "trihlavLib/trihlavCannotCastImplementation.hpp"
#include "trihlavLib/trihlavVersion.hpp"

#include "trihlavWtMainPanelView.hpp"
#include "trihlavWtPswdChckView.hpp"
#include "trihlavWtKeyListView.hpp"

#include "trihlavWtViewIface.hpp"

using namespace Wt;
using namespace std;
using boost::locale::translate;

namespace trihlav {

const string toString(const PanelName& pName) {
	if(pName==PanelName::KeyList) {
		return "KeyList";
	} else if(pName==PanelName::PswdCheck) {
		return "PswdCheck";
	} else if(pName==PanelName::Settings) {
		return "Settings";
	} else {
		return "Unknown panel";
	}
}

void WtMainPanelView::add(const string& pLocalizedName, const PanelName& pName,KeyListViewIface&  pKeyListView){
	WtKeyListView* myKeyListView =
			dynamic_cast<WtKeyListView*>(&pKeyListView);
	if (myKeyListView== 0) {
		//TODO add rtti of the base type to the err msg
		throw CannotCastImplementation("WtKeyListView");
	}
	addView(pLocalizedName,pName,*myKeyListView);
}

void WtMainPanelView::add(const string& pLocalizedName, const PanelName& pName, PswdChckViewIface& pPswdChckView) {
	WtPswdChckView* myPswdChckView =
			dynamic_cast<WtPswdChckView*>(&pPswdChckView);
	if (myPswdChckView == 0) {
		//TODO add rtti of the base type to the err msg
		throw CannotCastImplementation("WtPswdChckView");
	}
	addView(pLocalizedName,pName,*myPswdChckView);
}

void WtMainPanelView::addView(const std::string& pLocalizedName, const PanelName& pName,WtViewIface&  pView) {
	WMenuItem* myItem = getLeftMenu()->addItem(pLocalizedName,
			pView.getWWidget());
	string myUrl("/"+toString(pName));
	myItem->setLink(
			Wt::WLink(Wt::WLink::InternalPath, myUrl.c_str()));
	myItem->triggered().connect(std::bind([=](){sigShowedPanel(pName);}));
}

/**
 * 	Create a m_Navigation bar with a link to a web page.
 *
 */
WtMainPanelView::WtMainPanelView() : m_View ( new WContainerWidget()) {
	// Create a m_Navigation bar with a link to a web page.
	setNavigation(new Wt::WNavigationBar(m_View));
	getNavigation()->setTitle(WString(translate("TRIHLAV OTP Server")),
			"http://www.google.com/search?q=One+Time+Password");
	getNavigation()->setResponsive(true);
	setContentsStack (new Wt::WStackedWidget(m_View));
	m_ContentsStack->addStyleClass("contents");
	// Setup a Left-aligned menu.
	setLeftMenu(new Wt::WMenu(m_ContentsStack, m_View));
	getNavigation()->addMenu(getLeftMenu(), Wt::AlignLeft);
	// Setup a Right-aligned menu.
	Wt::WMenu* rightMenu = new Wt::WMenu();
	getNavigation()->addMenu(rightMenu, Wt::AlignRight);
	// Create a popup submenu for the Help menu.
	Wt::WPopupMenu* popup = new Wt::WPopupMenu();
	const string myHelpText = "Showing Help: {1}\n"
			"Build version: "+Version::getVersion();
	popup->addItem("Contents");
	popup->addItem("Index");
	popup->addSeparator();
	popup->addItem(new WMenuItem("About"));
	popup->itemSelected().connect(
			std::bind(
					[=](Wt::WMenuItem* item) {
						Wt::WMessageBox* messageBox = new Wt::WMessageBox("Help",
								Wt::WString::fromUTF8(myHelpText).arg(item->text()), Wt::Information, Wt::Ok);
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
	m_View->addWidget(getContentsStack());
}

WtMainPanelView::~WtMainPanelView() {
	delete m_View;
}

WContainerWidget* WtMainPanelView::getNativeView() {
	return m_View;
}

} /* namespace trihlav */

