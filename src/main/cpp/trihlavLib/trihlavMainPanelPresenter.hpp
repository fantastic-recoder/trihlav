/*
 * trihlavMainPanelCntrl.hpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_MAIN_PANEL_PRESENTER_HPP_
#define TRIHLAV_MAIN_PANEL_PRESENTER_HPP_

#include <memory>

#include "trihlavLib/trihlavPresenterBase.hpp"
#include "trihlavLib/trihlavGlobals.hpp"

namespace trihlav {

    class FactoryIface;

    class KeyListPresenterIface;

    class PswdChckPresenterIface;

    enum class PanelName;

/**
 * Implementation of the top level UI presenter.
 */
    class MainPanelPresenter : virtual public PresenterBase {
        MainPanelViewIfacePtr m_MainPanelView;
        KeyListPresenterIfacePtr m_KeyListPresenter;
        PswdChckPresenterIfacePtr m_PswdChckPresenter;
    public:
        MainPanelPresenter(FactoryIface &pFactory);

        virtual ~MainPanelPresenter();

        virtual ViewIface &getView();

        virtual void setupUi();

        virtual void showedPanel(const PanelName pPanel);
    };

} /* namespace trihlav */

#endif /* TRIHLAV_MAIN_PANEL_PRESENTER_HPP_ */
