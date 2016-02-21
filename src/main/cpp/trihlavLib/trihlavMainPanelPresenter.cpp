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

ViewIface* MainPanelPresenter::getView() {
	return itsMainPanelView;
}

void MainPanelPresenter::setupUi() {
	IPswdChckView& myPswdChckView=itsPswdChckPresenter->getView();
	itsMainPanelView->add("Password check",myPswdChckView);
	KeyListViewIface& myKeyListView=itsKeyListPresenter->getView();
	itsMainPanelView->add("Key list",myKeyListView);
}

} /* namespace trihlav */
