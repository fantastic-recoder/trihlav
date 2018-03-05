#include "../../main/cpp/trihlavSrv/trihlavWtMessageView.hpp"

#include <stdexcept>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include <Wt/WMessageBox.h>

using Wt::WMessageBox;
using Wt::Icon;
using Wt::StandardButton;
using std::bind;

namespace trihlav {

    WtMessageView::WtMessageView() {
        BOOST_LOG_NAMED_SCOPE("WtMessageView::WtMessageView");
    }

    void WtMessageView::showMessage(const std::string &pHeader,
                                    const std::string &pMsg) {
        BOOST_LOG_NAMED_SCOPE("WtMessageView::showMessage");
        WMessageBox *myMsgBox = new Wt::WMessageBox( //
                pHeader.c_str(),
                pMsg.c_str(),
                Icon::Information,
                StandardButton::Ok
        );
        myMsgBox->buttonClicked().connect(bind([=]() { delete myMsgBox; }));
        myMsgBox->show();
    }

    void WtMessageView::ask(const std::string &pHeader,
                            const std::string &pMsg, TCallback pCallback) {
        BOOST_LOG_NAMED_SCOPE("WtMessageView::ask");
        WMessageBox *myMsgBox = new Wt::WMessageBox( //
                pHeader.c_str(),
                pMsg.c_str(),
                Icon::Question,
                StandardButton::Ok | StandardButton::Cancel
        );
        myMsgBox->buttonClicked().connect(
                bind([=]() {
                    pCallback(myMsgBox->buttonResult() == StandardButton::Ok);
                    delete myMsgBox;
                })
        );
        myMsgBox->show();
    }

    WtMessageView::~WtMessageView() {
        BOOST_LOG_NAMED_SCOPE("WtMessageView::~WtMessageView");
    }

} /* namespace trihlav */
