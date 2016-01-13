/*
 * trihlavIPanel.hpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_I_PANEL_HPP_
#define TRIHLAV_I_PANEL_HPP_

namespace trihlav {

class IWidget;

class IPanel {
public:
	virtual ~IPanel(){}
	virtual void setupUi()=0;
};

}  // namespace trihlav

#endif // TRIHLAV_I_PANEL_HPP_
