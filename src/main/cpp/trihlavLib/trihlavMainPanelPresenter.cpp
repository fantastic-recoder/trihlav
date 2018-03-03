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

    MainPanelPresenter::MainPanelPresenter(FactoryIface &pFactory) :
            PresenterBase(pFactory),
            m_KeyListPresenter(pFactory.createKeyListPresenter()),
            m_PswdChckPresenter(pFactory.createPswdChckPresenter()),
            m_MainPanelView(pFactory.createMainPanelView()) {
    }

    MainPanelPresenter::~MainPanelPresenter() {
    }

    ViewIface &MainPanelPresenter::getView() {
        return *m_MainPanelView;
    }

    void MainPanelPresenter::setupUi() {
        getFactory().getSettings().load();
        PswdChckViewIface &myPswdChckView = m_PswdChckPresenter->getView();
        m_MainPanelView->add(translate("Password check"), PanelName::PswdCheck, myPswdChckView);
        KeyListViewIface &myKeyListView = m_KeyListPresenter->getView();
        m_MainPanelView->add(translate("Key list"), PanelName::KeyList, myKeyListView);
        m_MainPanelView->sigShowedPanel.connect([=](const PanelName &pPanel) { showedPanel(pPanel); });
    }

    void MainPanelPresenter::showedPanel(const PanelName pPanel) {
        BOOST_LOG_NAMED_SCOPE("MainPanelPresenter::showedPanel");

        if (pPanel == PanelName::KeyList) {
            m_KeyListPresenter->protectedAction();
        }
    }

} /* namespace trihlav */

