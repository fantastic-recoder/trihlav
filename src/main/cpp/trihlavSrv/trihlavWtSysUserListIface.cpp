/*
 * trihlavWtSysUserListIface.cpp
 *
 *  Created on: Sep 21, 2016
 *      Author: grobap
 */

#include <boost/locale.hpp>

#include <Wt/WDialog>
#include <Wt/WTable>
#include <Wt/WGridLayout>

#include "trihlavWtSysUserListIface.hpp"
#include "trihlavWtPushButton.hpp"


namespace trihlav {

using Wt::WTable;
using Wt::WDialog;
using Wt::WLength;
using Wt::WGridLayout;
using boost::locale::translate;
using U = Wt::WLength::Unit;

WtSysUserListView::WtSysUserListView() :
itsDlg(new WDialog), //
itsSysUserTable(new WTable),//
itsCancelBtn(new WtPushButton(translate("Cancel"))),//
itsOkBtn(new WtPushButton(translate("ok")))//

{
	itsDlg->setCaption(translate("Add key").str());
	itsDlg->setWidth(WLength(56, U::FontEm));
	WGridLayout* myTopLayout = new WGridLayout;
	{
		itsSysUserTable->elementAt(0, 0)->addWidget(new Wt::WText("login"));
		itsSysUserTable->elementAt(0, 1)->addWidget(new Wt::WText("Full name"));
		myTopLayout->addWidget(itsSysUserTable,0,0,3,8,Wt::AlignCenter|Wt::AlignMiddle);
	}
	{
		myTopLayout->addWidget(itsOkBtn,4,1,1,1,Wt::AlignCenter|Wt::AlignMiddle);
		myTopLayout->addWidget(itsCancelBtn,4,4,1,1,Wt::AlignCenter|Wt::AlignMiddle);
		itsCancelBtn->resize(WLength(11.0,U::FontEm),WLength(2.0,U::FontEm));
		itsOkBtn->resize(WLength(11.0,U::FontEm),WLength(2.0,U::FontEm));
	}
	itsDlg->contents()->setLayout(myTopLayout);
//	itsDlg->finished().connect(this, &WtYubikoOtpKeyView::finishedSlot);
//	itsCancelBtn->clicked().connect(itsDlg.get(), &WDialog::reject);
//	itsSaveBtn->clicked().connect(itsDlg.get(), &WDialog::accept);
}

}
/* namespace trihlav */
