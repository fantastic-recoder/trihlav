/*
 * trihlavSysUserListPresenter.cpp
 *
 *  Created on: Sep 21, 2016
 *      Author: grobap
 */

#include <algorithm>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavLib/trihlavFactoryIface.hpp"
#include "trihlavLib/trihlavSysUserListViewIface.hpp"
#include "trihlavLib/trihlavSysUserListPresenter.hpp"

using std::string;
using std::copy;
using trihlav::SysUser;
using trihlav::OsIface;

namespace trihlav {

    SysUserListPresenter::SysUserListPresenter(FactoryIface &pFactory) :
            PresenterBase(pFactory), m_SysUsers(new SysUsers()), m_CurrentUser(
            m_SysUsers->end()) {
        BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::SysUserListPresenter");
        getView().selectionChangedSig.connect([=](int pIdx) { selectedUser(pIdx); });
        getView().sigDialogFinished.connect([=](bool pAccepted) { accepted(pAccepted); });
    }

    SysUserListViewIface &SysUserListPresenter::getView() {
        BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::getView");
        if (!m_View) {
            m_View = getFactory().createSysUserListView();
        }
        return *m_View;
    }

    const string SysUserListPresenter::getSelectedSysUser() const {
        BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::getSelectedSysUser");
        static const string K_EMPTY;
        if (m_CurrentUser != m_SysUsers->end()) {
            return m_CurrentUser->str();
        }
        return K_EMPTY;
    }

    void SysUserListPresenter::show() {
        BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::show");
        OsIface &myOs{getFactory().getOsIface()};
        const SysUsers myUsers{myOs.getSysUsers(getFactory().getSettings())};
        m_SysUsers->clear();
        m_SysUsers->resize(myUsers.size());
        copy(myUsers.begin(), myUsers.end(), m_SysUsers->begin());
        m_CurrentUser = m_SysUsers->end();
        getView().show(*m_SysUsers);
    }

    SysUserListPresenter::~SysUserListPresenter() {
        BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::~SysUserListPresenter");
    }

    void SysUserListPresenter::selectedUser(int pIdx) {
        BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::selectedUser");
        if (pIdx >= 0 || pIdx < m_SysUsers->size()) {
            auto mySelected = getView().getRow(pIdx);
            BOOST_LOG_TRIVIAL(debug) << "Selected " << std::get<0>(mySelected);
            m_CurrentUser = (m_SysUsers->begin() += pIdx);
        }
    }

    void SysUserListPresenter::accepted(const bool pAccepted) {
        BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::accepted");
        if (pAccepted) {
            BOOST_LOG_TRIVIAL(debug) << "accepted";
            this->userSelectedSig();
        }
    }

}
/* namespace trihlav */

