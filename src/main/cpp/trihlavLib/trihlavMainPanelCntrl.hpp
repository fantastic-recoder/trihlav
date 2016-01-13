/*
 * trihlavMainPanelCntrl.hpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_MAINPANELCNTRL_HPP_
#define TRIHLAV_MAINPANELCNTRL_HPP_

#include "trihlavLib/trihlavICntrl.hpp"

namespace trihlav {

class IMainPanelView;

class MainPanelCntrl : virtual public ICntrl {
	IMainPanelView* itsView;
public:
	MainPanelCntrl();
	virtual ~MainPanelCntrl();
	virtual IPanel* getView();
};

} /* namespace trihlav */

#endif /* TRIHLAV_MAINPANELCNTRL_HPP_ */
