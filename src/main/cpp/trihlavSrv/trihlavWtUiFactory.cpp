/*
 * trihlavWtUiFactory.cpp
 *
 *  Created on: 12.01.2016
 *      Author: grobap
 */

#include "trihlavLib/trihlavGetUiFactory.hpp"

#include "trihlavWtUiFactory.hpp"
#include "trihlavWtMainPanelView.hpp"

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
}

IPswdChckView* WtUiFactory::createPswdChckView() const {
}

} /* namespace trihlav */
