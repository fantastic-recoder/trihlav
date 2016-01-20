/*
 * trihlavMainPanelCntrl.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include "trihlavLib/trihlavIMainPanelView.hpp"
#include "trihlavLib/trihlavIKeyListPresenter.hpp"
#include "trihlavLib/trihlavIPswdChckPresenter.hpp"

#include "trihlavLib/trihlavMainPanelPresenter.hpp"
#include "trihlavIFactory.hpp"

namespace trihlav {

MainPanelPresenter::MainPanelPresenter(IFactory& pFactory) :
		IPresenter(pFactory),
		itsKeyListPresenter(pFactory.createKeyListPresenter()),
		itsPswdChckPresenter(pFactory.createPswdChckPresenter()),
		itsMainPanelView(pFactory.createMainPanelView())
{
	;
}

MainPanelPresenter::~MainPanelPresenter() {
}

IView* MainPanelPresenter::getView() {
	return itsMainPanelView;
}

void MainPanelPresenter::setupUi() {
	itsMainPanelView->setupUi();
}

} /* namespace trihlav */
