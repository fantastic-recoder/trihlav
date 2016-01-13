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

#include "trihlavWtMainPanelView.hpp"
#include "trihlavApp.hpp"

using namespace Wt;

namespace trihlav {

App::App(const WEnvironment& pEnv) :
		WApplication(pEnv) {
	setTitle("Trihlav server");               // application title
	itsMainPanelCntrl=new MainPanelCntrl();
	trihlav::IPanel* myIMainPanelView = itsMainPanelCntrl->getView();
	WtMainPanelView* myMainPanelView = dynamic_cast<WtMainPanelView*>
		(myIMainPanelView);
	root()->addWidget(myMainPanelView->getNativeView());
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
