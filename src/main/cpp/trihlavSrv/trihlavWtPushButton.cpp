/*
 * trihlavWtPushButton.cpp
 *
 *  Created on: 27.01.2016
 *      Author: grobap
 */

#include "trihlavWtPushButton.hpp"

namespace trihlav {

    WtPushButton::WtPushButton(const std::string &pText)
            : Wt::WPushButton(pText) {
        this->clicked().connect(std::bind([=] { pressed(); }));
    }

} /* namespace trihlav */
