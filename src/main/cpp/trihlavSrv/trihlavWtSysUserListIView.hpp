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
	class WTableView;
	class WDialog;
}

#include "trihlavLib/trihlavSysUserListViewIface.hpp"

#include "trihlavWtDialogView.hpp"

namespace trihlav {

class WtPushButton;
class WtSysUserListModel;

class WtSysUserListView: virtual public WtDialogView, virtual public SysUserListViewIface {
public:
	WtSysUserListView();
	virtual void show(const SysUsers& pUsers) override;
    virtual int getSelected() override;
    virtual const UserRow_t& getRow(int pId) const override;

private:

	void selectionChanged();

	Wt::WTableView* m_SysUserTable;
	WtSysUserListModel* m_DtaMdl;   ///< Data model for the view.
};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_SYS_USER_LIST_VIEW_IFACE_HPP_ */
