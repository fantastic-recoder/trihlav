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

IMainPanelView* WtUiFactory::createMainPanelView() const {
	return new WtMainPanelView();
}

IFactory& getUiFactory() {
	static WtUiFactory theWtUiFactory;
	return theWtUiFactory;
}

IKeyListView* WtUiFactory::createKeyListView() const {
	return new WtKeyListView();
}

IPswdChckView* WtUiFactory::createPswdChckView() const {
	return new WtPswdChckView();
}

IYubikoOtpKeyView* WtUiFactory::createYubikoOtpKeyView() const {
	return new WtYubikoOtpKeyView();
}

} /* namespace trihlav */
