/*
 * trihlavWtSysUserListIface.cpp
 *
 *  Created on: Sep 21, 2016
 *      Author: grobap
 */

#include <boost/locale.hpp>

#include <Wt/WDialog>
#include <Wt/WTable>
#include <Wt/WFitLayout>
#include <Wt/WGridLayout>
#include <Wt/WScrollArea>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include "trihlavWtPushButton.hpp"
#include "trihlavWtSysUserListIView.hpp"

namespace {
	static const Wt::WLength K_DLG_H(42.0, Wt::WLength::Unit::FontEm);
	static const Wt::WLength K_DLG_W(32.0, Wt::WLength::Unit::FontEm);
}

namespace trihlav {

using Wt::WTable;
using Wt::WDialog;
using Wt::WLength;
using Wt::WGridLayout;
using Wt::WFitLayout;
using Wt::WScrollArea;

using Wt::WHBoxLayout;
using Wt::WVBoxLayout;

using boost::locale::translate;
using U = Wt::WLength::Unit;

WtSysUserListView::WtSysUserListView() :
		itsDlg(new WDialog), //
		itsSysUserTable(new WTable), //
		itsCancelBtn(new WtPushButton(translate("Cancel"))), //
		itsOkBtn(new WtPushButton(translate("ok"))) //

{
	itsDlg->setCaption(translate("Add key").str());
	itsDlg->setObjectName("WtSysUserListView");
	itsDlg->resize(K_DLG_W, K_DLG_H);
	WVBoxLayout* myContentLayout = new WVBoxLayout;
	{
		itsSysUserTable->setObjectName("SysUserTable");
		itsSysUserTable->setHeaderCount(1, Wt::Orientation::Horizontal);
		myContentLayout->setStretchFactor(itsSysUserTable, 1);
		myContentLayout->addWidget(itsSysUserTable);
	}
	WHBoxLayout* myBtnLayout = new WHBoxLayout;
	{
		itsCancelBtn->resize(WLength(11.0, U::FontEm), WLength(4.0, U::FontEm));
		itsOkBtn->resize(WLength(11.0, U::FontEm), WLength(4.0, U::FontEm));
		myBtnLayout->addWidget(itsOkBtn);
		myBtnLayout->addWidget(itsCancelBtn);
	}
	itsDlg->contents()->setLayout(myContentLayout);
	itsDlg->footer()->setLayout(myBtnLayout);
	itsDlg->setResizable(true);
	itsDlg->finished().connect(this, &WtSysUserListView::finishedSlot);
	itsCancelBtn->clicked().connect(itsDlg.get(), &WDialog::reject);
	itsOkBtn->clicked().connect(itsDlg.get(), &WDialog::accept);
}

void WtSysUserListView::show(const SysUsers& pUsers) {
	BOOST_LOG_NAMED_SCOPE("WtSysUserListView::show");
	int myCnt = 0;
	itsSysUserTable->clear();
	itsSysUserTable->elementAt(0, 0)->addWidget(
			new Wt::WText(translate("System login").str()));
	itsSysUserTable->elementAt(0, 1)->addWidget(
			new Wt::WText(translate("Full name").str()));
	for (const SysUser& myUser : pUsers) {
		myCnt++;
		itsSysUserTable->elementAt(myCnt, 0)->addWidget(
				new Wt::WText(myUser.itsLogin));
		itsSysUserTable->elementAt(myCnt, 1)->addWidget(
				new Wt::WText(myUser.itsFullName));
	}
	BOOST_LOG_TRIVIAL(debug)<<"System users loaded.";
	itsDlg->setModal(true);
	itsDlg->resize(K_DLG_W, K_DLG_H);
	itsDlg->show();
}

void WtSysUserListView::finishedSlot(WDialog::DialogCode pCode) {
	acceptedSig(pCode == WDialog::DialogCode::Accepted);
}

}
/* namespace trihlav */
