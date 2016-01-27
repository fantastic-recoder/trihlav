/*
 * trihlavIButton.hpp
 *
 *  Created on: 26.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_IBUTTON_HPP_
#define TRIHLAV_IBUTTON_HPP_

#include <boost/signals2.hpp>

namespace trihlav {
	/**
	 * Interface to push-button UI element.
	 */
	class IButton {
	public:
		/// Hide the underlying boost signal.
		typedef boost::signals2::signal<void()> PressedSignal;

		/**
		 * Button pressed event is signaling via this member.
		 */
		virtual PressedSignal& getPressedSignal(){
			return itsPressedSignal;
		}
		/**
		 * Button pressed event is signaling via this member.
		 */
		virtual const PressedSignal& getPressedSignal()const {
			return itsPressedSignal;
		}
		virtual ~IButton(){};
		virtual void pressed() { itsPressedSignal(); }

		/**
		 * @return Buttons label value in UTF8.
		 */
		virtual const std::string getText() const = 0;

		/**
		 * @param pText Set the button-label value in UTF8.
		 */
		virtual void setText( const std::string& pText) = 0;
	private:
		PressedSignal itsPressedSignal;
	};
}

#endif /* TRIHLAV_IBUTTON_HPP_ */
