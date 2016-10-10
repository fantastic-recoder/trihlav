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

#include "trihlavWtPushButton.hpp"
#include "trihlavWtSysUserListIView.hpp"

namespace trihlav {

using Wt::WTable;
using Wt::WDialog;
using Wt::WLength;
using Wt::WGridLayout;
using Wt::WFitLayout;
using boost::locale::translate;
using U = Wt::WLength::Unit;

WtSysUserListView::WtSysUserListView() :
		itsDlg(new WDialog), //
		itsSysUserTable(new WTable), //
		itsCancelBtn(new WtPushButton(translate("Cancel"))), //
		itsOkBtn(new WtPushButton(translate("ok"))) //

{
	itsDlg->setCaption(translate("Add key").str());
	itsDlg->setWidth(WLength(56.0, U::FontEm));
	WGridLayout* myContentLayout = new WGridLayout;
	{
		itsSysUserTable->setHeaderCount(1,Wt::Orientation::Horizontal);
		myContentLayout->addWidget(itsSysUserTable, 0, 0, 1, 5);
	}
	{
		myContentLayout->addWidget(itsOkBtn, 1, 1, 1, 1, Wt::AlignBottom|Wt::AlignMiddle);
		myContentLayout->addWidget(itsCancelBtn, 1, 4, 1, 1, Wt::AlignBottom|Wt::AlignMiddle);
		itsCancelBtn->resize(WLength(11.0, U::FontEm), WLength(2.0, U::FontEm));
		itsOkBtn->resize(WLength(11.0, U::FontEm), WLength(2.0, U::FontEm));
	}
	myContentLayout->setRowStretch(0,1);
	itsDlg->contents()->resize(WLength(100.0, U::Percentage), WLength(100.0, U::Percentage));
	itsDlg->contents()->setLayout(myContentLayout);
	itsDlg->finished().connect(this, &WtSysUserListView::finishedSlot);
	itsCancelBtn->clicked().connect(itsDlg.get(), &WDialog::reject);
	itsOkBtn->clicked().connect(itsDlg.get(), &WDialog::accept);
}

void WtSysUserListView::show(const SysUsers& pUsers) {
	int myCnt = 0;
	itsSysUserTable->clear();
	itsSysUserTable->elementAt(0, 0)->addWidget(new Wt::WText("login"));
	itsSysUserTable->elementAt(0, 1)->addWidget(new Wt::WText("Full name"));
	for (const SysUser& myUser : pUsers) {
		myCnt++;
		itsSysUserTable->elementAt(myCnt, 0)->addWidget(
				new Wt::WText(myUser.itsLogin));
		itsSysUserTable->elementAt(myCnt, 1)->addWidget(
				new Wt::WText(myUser.itsFullName));
	}
	itsDlg->exec();
}

void WtSysUserListView::finishedSlot(WDialog::DialogCode pCode) {
	acceptedSig(pCode == WDialog::DialogCode::Accepted);
}

}
/* namespace trihlav */
