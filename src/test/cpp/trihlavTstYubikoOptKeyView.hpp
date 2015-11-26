/*
 * trihlavTstYubikoOptKey.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_TST_YUBIKO_OPT_KEY_VIEW_HPP_
#define TRIHLAV_TST_YUBIKO_OPT_KEY_VIEW_HPP_

#include <trihlavLib/trihlavIYubikoOptKeyView.hpp>

#include "trihlavTstLineEdit.hpp"

namespace trihlav {

class TstYubikoOptKeyView: public IYubikoOptKeyView {
	TstLineEdit itsPrefix;
public:
	TstYubikoOptKeyView() {}

	virtual ~TstYubikoOptKeyView();

	virtual const ILineEdit& getPublicIdentity() const {
		return itsPrefix;
	}

	virtual ILineEdit& getPublicIdentity() {
		return itsPrefix;
	}
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_TST_YUBIKO_OPT_KEY_VIEW_HPP_ */
