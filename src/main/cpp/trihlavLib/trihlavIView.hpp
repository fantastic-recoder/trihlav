/*
 * trihlavIPanel.hpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_I_VIEW_HPP_
#define TRIHLAV_I_VIEW_HPP_

#include <boost/utility.hpp>

namespace trihlav {

class IWidget;

/**
 * Parent to all view interfaces.
 */
class IView : boost::noncopyable {
public:
	virtual ~IView(){}
};

}  // namespace trihlav

#endif // TRIHLAV_I_VIEW_HPP_
