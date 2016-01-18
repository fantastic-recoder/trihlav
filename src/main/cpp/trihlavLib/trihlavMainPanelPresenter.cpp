/*
 * trihlavMainPanelCntrl.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include "trihlavLib/trihlavMainPanelPresenter.hpp"

#include "trihlavLib/trihlavGetUiFactory.hpp"

namespace trihlav {

MainPanelPresenter::MainPanelPresenter() {
	IUiFactory& myFactory = getUiFactory();
	itsView = myFactory.createIMainPanelView();
}

MainPanelPresenter::~MainPanelPresenter() {
	delete itsView;
}

IView* MainPanelPresenter::getView() {
	return itsView;
}

void MainPanelPresenter::setupUi() {
	itsView->setupUi();
}

} /* namespace trihlav */
