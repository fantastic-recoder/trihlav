/*
 * trihlavSysUserListViewIface.hpp
 *
 *  Created on: Sep 21, 2016
 *      Author: grobap
 */

#ifndef SRC_MATRIHLAV_SYS_USER_LIST_VIEW_IFACE_HPP_
#define SRC_MATRIHLAV_SYS_USER_LIST_VIEW_IFACE_HPP_

#include <tuple>
#include <boost/signals2.hpp>

#include "trihlavLib/trihlavOsIface.hpp"
#include "trihlavLib/trihlavDialogViewIface.hpp"

namespace trihlav {

class SysUserListViewIface : virtual public DialogViewIface {
public:
    using AcceptedSignal= ::boost::signals2::signal<void()>;
    using SelectionChangedSignal= ::boost::signals2::signal<void(int)>;
    using UserRow_t = ::std::tuple<std::string,std::string>;

    /**
	 * Should be fired by the UI when user selects a row. The ids of the rows are passed.
	 */
	SelectionChangedSignal selectionChangedSig;

    AcceptedSignal acceptedSig;

    virtual void show(const SysUsers& pUsers)=0;

    virtual int getSelected()=0;

    virtual const UserRow_t& getRow(int pId) const =0;

};

} /* namespace trihlav */

#endif /* SRC_MATRIHLAV_SYS_USER_LIST_VIEW_IFACE_HPP_ */
