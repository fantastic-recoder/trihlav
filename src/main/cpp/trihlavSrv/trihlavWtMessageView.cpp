#include "../../main/cpp/trihlavSrv/trihlavWtMessageView.hpp"

#include <stdexcept>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>



namespace trihlav {

WtMessageView::WtMessageView() {
	BOOST_LOG_NAMED_SCOPE("WtMessageView::WtMessageView");
}

void WtMessageView::showMessage(const std::string& pHeader,
		const std::string& pMsg) {
	BOOST_LOG_NAMED_SCOPE("WtMessageView::showMessage");
	throw new std::runtime_error("Not yet implemented ;-(");
}

WtMessageView::~WtMessageView() {
	BOOST_LOG_NAMED_SCOPE("WtMessageView::~WtMessageView");
}

} /* namespace trihlav */
