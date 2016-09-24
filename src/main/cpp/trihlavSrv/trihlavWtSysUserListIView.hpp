/*
 * trihlavWtSysUserListIface.hpp
 *
 *  Created on: Sep 21, 2016
 *      Author: grobap
 */

#ifndef TRIHLAV_WT_SYS_USER_LIST_VIEW_IFACE_HPP_
#define TRIHLAV_WT_SYS_USER_LIST_VIEW_IFACE_HPP_

#include <memory>

namespace Wt {
	class WTable;
	class WDialog;
}

#include "trihlavLib/trihlavSysUserListViewIface.hpp"

namespace trihlav {

class WtPushButton;

class WtSysUserListView: public SysUserListViewIface {
public:
	WtSysUserListView();
	virtual void show(const SysUsers& pUsers) override;
    virtual void finishedSlot(Wt::WDialog::DialogCode pCode);

private:
	Wt::WTable* itsSysUserTable;
	WtPushButton* itsCancelBtn;
	WtPushButton* itsOkBtn;
    std::unique_ptr<Wt::WDialog> itsDlg;
};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_SYS_USER_LIST_VIEW_IFACE_HPP_ */
