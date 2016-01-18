/*
 * trihlavMainPanelCntrl.hpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_MAIN_PANEL_PRESENTER_HPP_
#define TRIHLAV_MAIN_PANEL_PRESENTER_HPP_

#include "trihlavIPresenter.hpp"

namespace trihlav {

class IMainPanelView;
class IKeyListPresenter;
class IPswdChckPresenter;

/**
 * Implementation of the top level UI presenter.
 */
class MainPanelPresenter : virtual public IPresenter {
	IMainPanelView*     itsView;
	IKeyListPresenter*  itsKeyList;
	IPswdChckPresenter* itsPswdChck;
public:
	MainPanelPresenter();
	virtual ~MainPanelPresenter();
	virtual IView* getView();
	virtual void setupUi();
};

} /* namespace trihlav */

#endif /* TRIHLAV_MAIN_PANEL_PRESENTER_HPP_ */
