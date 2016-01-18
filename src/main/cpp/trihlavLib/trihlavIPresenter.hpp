/*
 * trihlavICntrl.hpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_I_PRESENTER_HPP_
#define TRIHLAV_I_PRESENTER_HPP_

#include "trihlavIView.hpp"

namespace trihlav {

/**
 * Common functionality to all controllers.
 * Every controller has an view.
 */
class IPresenter {
	virtual IView* getView()=0;
};

} /* namespace trihlav */

#endif /* TRIHLAV_I_PRESENTER_HPP_ */
