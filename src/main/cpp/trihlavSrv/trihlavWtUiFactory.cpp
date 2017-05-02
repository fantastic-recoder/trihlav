/*
 * trihlavWtUiFactory.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include <Wt/WDialog>

#include "trihlavLib/trihlavGetUiFactory.hpp"
#include "trihlavLib/trihlavOsIface.hpp"

#include "trihlavWtUiFactory.hpp"
#include "trihlavWtPswdChckView.hpp"
#include "trihlavWtMainPanelView.hpp"
#include "trihlavWtKeyListView.hpp"
#include "trihlavWtMessageView.hpp"
#include "trihlavWtSysUserListIView.hpp"
#include "trihlavWtYubikoOtpKeyView.hpp"
#include "trihlavWtLoginView.hpp"

namespace trihlav {

WtUiFactory::WtUiFactory() {
	// TODO Auto-generated constructor stub

}

WtUiFactory::~WtUiFactory() {
	// TODO Auto-generated destructor stub
}

MainPanelViewIfacePtr WtUiFactory::createMainPanelView() {
	return MainPanelViewIfacePtr(new WtMainPanelView());
}

FactoryIface& getUiFactory() {
	static WtUiFactory theWtUiFactory;
	return theWtUiFactory;
}

KeyListViewIfacePtr WtUiFactory::createKeyListView() {
	return KeyListViewIfacePtr(new WtKeyListView());
}

PswdChckViewIfacePtr WtUiFactory::createPswdChckView() {
	return PswdChckViewIfacePtr(new WtPswdChckView());
}

YubikoOtpKeyViewIfacePtr WtUiFactory::createYubikoOtpKeyView() {
	return YubikoOtpKeyViewIfacePtr(new WtYubikoOtpKeyView());
}

MessageViewIfacePtr WtUiFactory::createMessageView() {
	return MessageViewIfacePtr(new WtMessageView());
}

SysUserListViewIfacePtr WtUiFactory::createSysUserListView() {
	return SysUserListViewIfacePtr(new WtSysUserListView());
}

LoginViewIfacePtr WtUiFactory::createLoginView() {
	return LoginViewIfacePtr(new WtLoginView());
}

} /* namespace trihlav */
