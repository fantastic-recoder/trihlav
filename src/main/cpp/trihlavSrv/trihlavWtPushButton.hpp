/*
 * trihlavWtPushButton.hpp
 *
 *  Created on: 27.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_WT_PUSH_BUTTON_HPP_
#define TRIHLAV_WT_PUSH_BUTTON_HPP_

#include <Wt/WPushButton.h>
#include <Wt/WString.h>

#include "trihlavLib/trihlavButtonIface.hpp"

namespace trihlav {

/**
 * Implement trihlav::IButton using Wt::WPushButton.
 */
class WtPushButton: virtual public ButtonIface,  virtual public Wt::WPushButton {
public:
	/**
	 * @param pText initial value for the label.
	 * @see setText( const std::string& )
	 */
    explicit WtPushButton(const std::string &pText);

    virtual ~WtPushButton() = default;

    const std::string getText() const override {
		return text().toUTF8();
	}

    void setText(const std::string &pText) override {
		Wt::WPushButton::setText(Wt::WString::fromUTF8(pText));
    }

    void setEnabled(bool pEnabled) override {
        Wt::WPushButton::setEnabled(pEnabled);
    }

    bool isEnabled() const override {
        return Wt::WPushButton::isEnabled();
    }
};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_PUSH_BUTTON_HPP_ */
