/*
 * trihlavSysUserListPresenter.hpp
 *
 *  Created on: Sep 21, 2016
 *      Author: grobap
 */

#ifndef TRIHLAV_SYS_USER_LIST_PRESENTER_HPP_
#define TRIHLAV_SYS_USER_LIST_PRESENTER_HPP_

#include "trihlavPresenterBase.hpp"

namespace trihlav {

class SysUserListPresenter  : virtual public PresenterBase {
public:
	SysUserListPresenter(FactoryIface& pFactory) : PresenterBase(pFactory) {
	}
};

} /* namespace trihlav */

#endif /* TRIHLAV_SYS_USER_LIST_PRESENTER_HPP_ */
