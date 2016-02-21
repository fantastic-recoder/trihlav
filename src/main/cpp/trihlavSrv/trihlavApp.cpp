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
#include <Wt/WBootstrapTheme>

#include "trihlavWtMainPanelView.hpp"
#include "trihlavApp.hpp"
#include "trihlavLib/trihlavMainPanelPresenter.hpp"
#include "trihlavLib/trihlavGetUiFactory.hpp"

using namespace Wt;

namespace trihlav {

App::App(const WEnvironment& pEnv) :
		WApplication(pEnv) {
	setTitle("Trihlav server");               // application title
	useStyleSheet("style/everywidget.css");
	useStyleSheet("style/dragdrop.css");
	useStyleSheet("style/combostyle.css");
	useStyleSheet("style/pygments.css");
	useStyleSheet("style/layout.css");
	//useStyleSheet("style/CSSexample.css");
	setTheme(new WBootstrapTheme(this));

	itsMainPanelCntrl=new MainPanelPresenter(getUiFactory());
	trihlav::ViewIface* myIMainPanelView = itsMainPanelCntrl->getView();
	WtMainPanelView* myMainPanelView = dynamic_cast<WtMainPanelView*>
		(myIMainPanelView);
	root()->addWidget(myMainPanelView->getNativeView());
	itsMainPanelCntrl->setupUi();
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
