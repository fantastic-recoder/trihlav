/*
 * trihlavMainPanelCntrl.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include "trihlavLib/trihlavMainPanelPresenter.hpp"

#include "trihlavFactoryIface.hpp"
#include "trihlavKeyListPresenterIface.hpp"
#include "trihlavMainPanelViewIface.hpp"
#include "trihlavPswdChckPresenterIface.hpp"

namespace trihlav {

MainPanelPresenter::MainPanelPresenter(FactoryIface& pFactory) :
		PresenterBase(pFactory),
		itsKeyListPresenter(pFactory.createKeyListPresenter()),
		itsPswdChckPresenter(pFactory.createPswdChckPresenter()),
		itsMainPanelView(pFactory.createMainPanelView())
{
}

MainPanelPresenter::~MainPanelPresenter() {
}

ViewIface* MainPanelPresenter::getView() {
	return itsMainPanelView;
}

void MainPanelPresenter::setupUi() {
	PswdChckViewIface& myPswdChckView=itsPswdChckPresenter->getView();
	itsMainPanelView->add("Password check",myPswdChckView);
	KeyListViewIface& myKeyListView=itsKeyListPresenter->getView();
	itsMainPanelView->add("Key list",myKeyListView);
	itsKeyListPresenter->reloadKeyList();
}

} /* namespace trihlav */
