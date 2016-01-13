/*
 * App.cpp
 *
 *  Created on: 30.08.2015
 *      Author: grobap
 */

#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WWidget>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>

#include "trihlavLib/trihlavMainPanelCntrl.hpp"
#include "trihlavLib/trihlavIWidget.hpp"

#include "trihlavApp.hpp"

using namespace Wt;

namespace trihlav {

App::App(const WEnvironment& pEnv) :
		WApplication(pEnv) {
	setTitle("Trihlav server");               // application title
	itsMainPanelCntrl=new MainPanelCntrl();
	IPanel* myMainPanelView = itsMainPanelCntrl->getView();
	void* myNativeView =
			myMainPanelView->getNativeView();
	WContainerWidget* myWMainPanelView =
			(WContainerWidget*)myNativeView;
	//root()->addWidget(myWMainPanelView);
	root()->addWidget(new WContainerWidget());
	// show some text
//	itsPwdEdit = new WLineEdit(root());    // allow text input
//	itsPwdEdit->setFocus();                // give focus
//
//	WPushButton *myChkBtn = new WPushButton("Check.", root());
//	// create a button
//	//myChkBtn->setMargin(5, WFlags::Side::Left);       // add 5 pixels margin
//
//	root()->addWidget(new WBreak());      // insert a line break
//
//	itsGreeting = new WText(root());        // empty text
//
//	// Connect signals with slots
//
//	myChkBtn->clicked().connect(SLOT(this, App::check));
//	itsPwdEdit->enterPressed().connect(SLOT(this, App::check));
}

/**
 * Check the password.
 */
void App::check() {
	/*
	 * Update the text, using text input into the nameEdit_ field.
	 */
    itsGreeting->setText("Hello there, " + itsPwdEdit->text()+" is invalid.");
}

App *App::createApplication(const WEnvironment& env) {
	/*
	 * You could read information from the environment to decide whether
	 * the user has permission to start a new application
	 */
	return new App(env);
}

App::~App() {
	delete itsMainPanelCntrl;
}

} /* namespace trihlav */
