/*
 * trihlavWtPushButton.hpp
 *
 *  Created on: 27.01.2016
 *      Author: grobap
 */

#ifndef TRIHLAV_WT_PUSH_BUTTON_HPP_
#define TRIHLAV_WT_PUSH_BUTTON_HPP_

#include <Wt/WPushButton>
#include <Wt/WString>

#include "../trihlavLib/trihlavButtonIface.hpp"

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
	WtPushButton(const std::string& pText);
	virtual ~WtPushButton();

	virtual const std::string getText() const {
		return text().toUTF8();
	}

	virtual void setText( const std::string& pText) {
		Wt::WPushButton::setText(Wt::WString::fromUTF8(pText));
	}

};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_PUSH_BUTTON_HPP_ */
