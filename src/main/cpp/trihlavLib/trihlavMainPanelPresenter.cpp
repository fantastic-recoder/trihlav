/*
 * trihlavMainPanelCntrl.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include <boost/locale.hpp>

#include "trihlavLib/trihlavLogApi.hpp"
#include "trihlavLib/trihlavMainPanelPresenter.hpp"
#include "trihlavLib/trihlavSettings.hpp"

#include "trihlavFactoryIface.hpp"
#include "trihlavKeyListPresenterIface.hpp"
#include "trihlavMainPanelViewIface.hpp"
#include "trihlavPswdChckPresenterIface.hpp"

using boost::locale::translate;

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

ViewIface& MainPanelPresenter::getView() {
	return *itsMainPanelView;
}

void MainPanelPresenter::setupUi() {
	getFactory().getSettings().load();
	PswdChckViewIface& myPswdChckView=itsPswdChckPresenter->getView();
	itsMainPanelView->add(translate("Password check"),PanelName::PswdCheck,myPswdChckView);
	KeyListViewIface& myKeyListView=itsKeyListPresenter->getView();
	itsMainPanelView->add(translate("Key list"),PanelName::KeyList,myKeyListView);
	itsMainPanelView->sigShowedPanel.connect([=](const PanelName& pPanel){showedPanel(pPanel);});
}

void MainPanelPresenter::showedPanel(const PanelName pPanel) {
	BOOST_LOG_NAMED_SCOPE("MainPanelPresenter::showedPanel");

	if(pPanel==PanelName::KeyList) {
		itsKeyListPresenter->reloadKeyList();
	}
}

} /* namespace trihlav */

