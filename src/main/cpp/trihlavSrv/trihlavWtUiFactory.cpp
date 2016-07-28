/*
 * trihlavWtUiFactory.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include "trihlavLib/trihlavGetUiFactory.hpp"
#include "trihlavLib/trihlavOsIface.hpp"

#include "trihlavWtUiFactory.hpp"
#include "trihlavWtPswdChckView.hpp"
#include "trihlavWtMainPanelView.hpp"
#include "trihlavWtKeyListView.hpp"
#include "trihlavWtMessageView.hpp"
#include "trihlavWtYubikoOtpKeyView.hpp"

namespace trihlav {

WtUiFactory::WtUiFactory() {
	// TODO Auto-generated constructor stub

}

WtUiFactory::~WtUiFactory() {
	// TODO Auto-generated destructor stub
}

MainPanelViewIface* WtUiFactory::createMainPanelView() {
	return new WtMainPanelView();
}

FactoryIface& getUiFactory() {
	static WtUiFactory theWtUiFactory;
	return theWtUiFactory;
}

KeyListViewIface* WtUiFactory::createKeyListView() {
	return new WtKeyListView();
}

PswdChckViewIface* WtUiFactory::createPswdChckView() {
	return new WtPswdChckView();
}

YubikoOtpKeyViewIface* WtUiFactory::createYubikoOtpKeyView() {
	return new WtYubikoOtpKeyView();
}

MessageViewIface* WtUiFactory::createMessageView() {
	return new WtMessageView();
}

} /* namespace trihlav */
