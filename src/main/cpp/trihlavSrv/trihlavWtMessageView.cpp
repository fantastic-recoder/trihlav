#include "../../main/cpp/trihlavSrv/trihlavWtMessageView.hpp"

#include <stdexcept>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include <Wt/WMessageBox>

using Wt::WMessageBox;
using Wt::Ok;

namespace trihlav {

WtMessageView::WtMessageView() {
	BOOST_LOG_NAMED_SCOPE("WtMessageView::WtMessageView");
}

void WtMessageView::showMessage(const std::string& pHeader,
		const std::string& pMsg) {
	BOOST_LOG_NAMED_SCOPE("WtMessageView::showMessage");
	WMessageBox::show(pHeader.c_str(),pMsg.c_str(),Ok);
}

WtMessageView::~WtMessageView() {
	BOOST_LOG_NAMED_SCOPE("WtMessageView::~WtMessageView");
}

} /* namespace trihlav */
