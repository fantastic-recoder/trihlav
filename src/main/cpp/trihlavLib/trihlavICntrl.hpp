/*
 * trihlavICntrl.hpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_I_CNTRL_HPP_
#define TRIHLAV_I_CNTRL_HPP_

#include "trihlavLib/trihlavIPanel.hpp"

namespace trihlav {

/**
 * Common functionality to all controllers.
 * Every controller has an view.
 */
class ICntrl {
	virtual IPanel* getView()=0;
};

} /* namespace trihlav */

#endif /* TRIHLAV_I_CNTRL_HPP_ */
