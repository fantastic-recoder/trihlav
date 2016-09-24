/*
 * trihlavSysUserListViewIface.hpp
 *
 *  Created on: Sep 21, 2016
 *      Author: grobap
 */

#ifndef SRC_MATRIHLAV_SYS_USER_LIST_VIEW_IFACE_HPP_
#define SRC_MATRIHLAV_SYS_USER_LIST_VIEW_IFACE_HPP_

#include <boost/signals2.hpp>

#include "trihlavLib/trihlavOsIface.hpp"

namespace trihlav {

class SysUserListViewIface {
public:
    typedef ::boost::signals2::signal<void(const bool)> AcceptedSignal ;

    AcceptedSignal acceptedSig;

    virtual void show(const SysUsers& pUsers)=0;
};

} /* namespace trihlav */

#endif /* SRC_MATRIHLAV_SYS_USER_LIST_VIEW_IFACE_HPP_ */
