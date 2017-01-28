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
	getView().selectionChangedSig.connect([=](int pIdx) {selectedUser(pIdx);});
	getView().sigDialogFinished.connect([=](bool pAccepted) {accepted(pAccepted);});
}

SysUserListViewIface& SysUserListPresenter::getView() {
	BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::getView");
	if (!itsView) {
		itsView = getFactory().createSysUserListView();
	}
	return *itsView;
}

const string SysUserListPresenter::getSelectedSysUser() const {
	BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::getSelectedSysUser");
	static const string K_EMPTY;
	if (itsCurrentUser != itsSysUsers->end()) {
		return itsCurrentUser->str();
	}
	return K_EMPTY;
}

void SysUserListPresenter::show() {
	BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::show");
	OsIface& myOs { getFactory().getOsIface() };
	const SysUsers myUsers { myOs.getSysUsers(getFactory().getSettings()) };
	itsSysUsers->clear();
	itsSysUsers->resize(myUsers.size());
	copy(myUsers.begin(), myUsers.end(), itsSysUsers->begin());
	itsCurrentUser = itsSysUsers->end();
	getView().show(*itsSysUsers);
}

SysUserListPresenter::~SysUserListPresenter() {
	BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::~SysUserListPresenter");
}

void SysUserListPresenter::selectedUser(int pIdx) {
	BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::selectedUser");
	if (pIdx >= 0 || pIdx < itsSysUsers->size()) {
		auto mySelected = getView().getRow(pIdx);
		BOOST_LOG_TRIVIAL(debug)<<"Selected " << std::get<0>(mySelected);
		itsCurrentUser = (itsSysUsers->begin() += pIdx);
	}
}

void SysUserListPresenter::accepted(const bool pAccepted) {
	BOOST_LOG_NAMED_SCOPE("SysUserListPresenter::accepted");
	if (pAccepted) {
		BOOST_LOG_TRIVIAL(debug)<<"accepted";
		this->userSelectedSig();
	}
}

}
/* namespace trihlav */

