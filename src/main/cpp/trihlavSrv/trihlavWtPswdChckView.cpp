/*
 * trihlavPswdChckView.cpp
 *
 *  Created on: 22.01.2016
 *      Author: grobap
 */

#include <Wt/WPanel>
#include <Wt/WWidget>
#include <Wt/WText>
#include "trihlavWtPswdChckView.hpp"

using namespace Wt;

namespace trihlav {

WtPswdChckView::WtPswdChckView() {
	itsMainPanel = new Wt::WText("Password 0");
}

WtPswdChckView::~WtPswdChckView() {
	// TODO Auto-generated destructor stub
}

WWidget*   WtPswdChckView::getWWidget() {
	return itsMainPanel;
}

void WtPswdChckView::setupUi() {
}

} /* namespace trihlav */

