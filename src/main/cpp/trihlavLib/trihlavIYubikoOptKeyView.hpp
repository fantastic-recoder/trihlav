/*
 * trihlavIYubikoOptKeyView.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_I_YUBIKO_OPT_KEY_VIEW_HPP_
#define TRIHLAV_I_YUBIKO_OPT_KEY_VIEW_HPP_

#include <trihlavLib/trihlavILineEdit.hpp>

namespace trihlavApi {

class IYubikoOptKeyView {
	virtual const ILineEdit& getPrefix() const=0;
	virtual ILineEdit& getPrefix()=0;
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_I_YUBIKO_OPT_KEY_VIEW_HPP_ */
