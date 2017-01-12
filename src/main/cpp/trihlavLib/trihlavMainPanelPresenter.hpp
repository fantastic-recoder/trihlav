/*
 * trihlavMainPanelCntrl.hpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_MAIN_PANEL_PRESENTER_HPP_
#define TRIHLAV_MAIN_PANEL_PRESENTER_HPP_

#include <memory>

#include "trihlavPresenterBase.hpp"

namespace trihlav {

class FactoryIface;
class MainPanelViewIface;
class KeyListPresenterIface;
class PswdChckPresenterIface;

/**
 * Implementation of the top level UI presenter.
 */
class MainPanelPresenter : virtual public PresenterBase {
	std::unique_ptr<MainPanelViewIface> itsMainPanelView;
	KeyListPresenterIface*  itsKeyListPresenter;
	PswdChckPresenterIface* itsPswdChckPresenter;
public:
	MainPanelPresenter(FactoryIface& pFactory);
	virtual ~MainPanelPresenter();
	virtual ViewIface& getView();
	virtual void setupUi();
};

} /* namespace trihlav */

#endif /* TRIHLAV_MAIN_PANEL_PRESENTER_HPP_ */
