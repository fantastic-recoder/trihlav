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

/**
 * Parent to all view interfaces.
 */
class IView {
public:
	virtual ~IView(){}

	/**
	 *
	 */
	virtual void setupUi()=0;
};

}  // namespace trihlav

#endif // TRIHLAV_I_PANEL_HPP_
