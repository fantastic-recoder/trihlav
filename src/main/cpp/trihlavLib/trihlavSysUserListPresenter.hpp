/*
 * trihlavSysUserListPresenter.hpp
 *
 *  Created on: Sep 21, 2016
 *      Author: grobap
 */

#ifndef TRIHLAV_SYS_USER_LIST_PRESENTER_HPP_
#define TRIHLAV_SYS_USER_LIST_PRESENTER_HPP_

#include <memory>
#include <boost/signals2.hpp>

#include "trihlavLib/trihlavOsIface.hpp"
#include "trihlavLib/trihlavPresenterBase.hpp"

namespace trihlav {

    class SysUserListViewIface;

    class SysUserListPresenter : virtual public PresenterBase {
    public:
        using UserSelectedSig = boost::signals2::signal<void()>;

        UserSelectedSig userSelectedSig;

        SysUserListPresenter(FactoryIface &pFactory);

        const std::string getSelectedSysUser() const;

        void show();

        virtual ~SysUserListPresenter();

        SysUserListViewIface &getView();

        void selectedUser(int pIdx);

        void accepted(bool);

    private:
        using SysUsersIt=SysUsers::const_iterator;

        std::unique_ptr<SysUsers> m_SysUsers;
        std::shared_ptr<SysUserListViewIface> m_View;
        SysUsersIt m_CurrentUser;
    };

} /* namespace trihlav */

#endif /* TRIHLAV_SYS_USER_LIST_PRESENTER_HPP_ */
