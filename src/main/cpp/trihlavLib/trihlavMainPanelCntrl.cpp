/*
 * trihlavMainPanelCntrl.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include "trihlavMainPanelCntrl.hpp"
#include "trihlavGetUiFactory.hpp"

namespace trihlav {

MainPanelCntrl::MainPanelCntrl() {
	IUiFactory& myFactory = getUiFactory();
	itsView = myFactory.createIMainPanelView();
}

MainPanelCntrl::~MainPanelCntrl() {
	delete itsView;
}

IPanel* MainPanelCntrl::getView() {
	return itsView;
}

} /* namespace trihlav */
