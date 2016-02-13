/*
 * trihlavWtUiFactory.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include "trihlavLib/trihlavGetUiFactory.hpp"

#include "trihlavWtUiFactory.hpp"
#include "trihlavWtPswdChckView.hpp"
#include "trihlavWtMainPanelView.hpp"
#include "trihlavWtKeyListView.hpp"
#include "trihlavWtYubikoOtpKeyView.hpp"

namespace trihlav {

WtUiFactory::WtUiFactory() {
	// TODO Auto-generated constructor stub

}

WtUiFactory::~WtUiFactory() {
	// TODO Auto-generated destructor stub
}

IMainPanelView* WtUiFactory::createMainPanelView() {
	return new WtMainPanelView();
}

IFactory& getUiFactory() {
	static WtUiFactory theWtUiFactory;
	return theWtUiFactory;
}

IKeyListView* WtUiFactory::createKeyListView() {
	return new WtKeyListView();
}

IPswdChckView* WtUiFactory::createPswdChckView() {
	return new WtPswdChckView();
}

IYubikoOtpKeyView* WtUiFactory::createYubikoOtpKeyView() {
	return new WtYubikoOtpKeyView();
}

IPswdChckPresenter* WtUiFactory::createPswdChckPresenter() {
	return nullptr;
}

YubikoOtpKeyPresenterI* WtUiFactory::createYubikoOtpKeyPresenter() {
	return nullptr;
}

} /* namespace trihlav */
