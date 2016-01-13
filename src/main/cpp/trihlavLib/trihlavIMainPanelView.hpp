/*
 * trihlavIMainPanelView.hpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_I_MAIN_PANEL_VIEW_HPP_
#define TRIHLAV_I_MAIN_PANEL_VIEW_HPP_

#include "trihlavLib/trihlavIPanel.hpp"

namespace trihlav {

class IMainPanelView : virtual public IPanel {
public:
	virtual ~IMainPanelView(){}
};

} // end namespace trihlav

#endif /* TRIHLAV_I_MAIN_PANEL_VIEW_HPP_ */
