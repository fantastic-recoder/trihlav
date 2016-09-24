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
#include "trihlavLib/trihlavOsIface.hpp"

using std::string;
using std::copy;
using trihlav::SysUser;
using trihlav::OsIface;

namespace trihlav {

SysUserListPresenter::SysUserListPresenter(FactoryIface& pFactory) :
		PresenterBase(pFactory), itsSysUsers(new SysUsers()), itsCurrentUser(
				itsSysUsers->end()) {
	BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::SysUserListPresenter");

}

SysUserListViewIface& SysUserListPresenter::getView() {
	BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::getView");
	if (!itsView) {
		itsView=getFactory().createSysUserListView();
	}
	return *itsView;
}

const string& SysUserListPresenter::getSelectedSysUser() const {
	BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::getSelectedSysUser");
	static const string K_EMPTY;
	if (itsCurrentUser != itsSysUsers->end()) {
		itsCurrentUser->itsLogin;
	}
	return K_EMPTY;
}

void SysUserListPresenter::show() {
	OsIface& myOs { getFactory().getOsIface() };
	SysUsers myUsers { myOs.getSysUsers() };
	itsSysUsers->clear();
	copy(myUsers.begin(), myUsers.end(), itsSysUsers->begin());
	itsCurrentUser=itsSysUsers->end();
	getView().show(*itsSysUsers);
}

SysUserListPresenter::~SysUserListPresenter() {
}

} /* namespace trihlav */

