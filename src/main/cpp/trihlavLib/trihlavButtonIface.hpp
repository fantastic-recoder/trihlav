/*
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
	der GNU General Public License, wie von der Free Software Foundation,
	Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
	veröffentlichten Version, weiterverbreiten und/oder modifizieren.

	Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
	OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
	Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
	Siehe die GNU General Public License für weitere Details.

	Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
	Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/

#ifndef TRIHLAV_BUTTON_IFACE_HPP_
#define TRIHLAV_BUTTON_IFACE_HPP_

#include <boost/signals2.hpp>

#include "trihlavLib/trihlavWidgetIface.hpp"

namespace trihlav {
	/**
	 * Interface to push-button UI element.
	 */
        class ButtonIface : virtual public WidgetIface {
	public:
		/// Hide the underlying boost signal.
		typedef boost::signals2::signal<void()> PressedSignal;

		/**
		 * Button pressed event is signaling via this member.
		 */
		PressedSignal pressedSig;

		virtual ~ButtonIface(){};

		/**
		 * Trigger button-pressed signal.
		 */
		virtual void pressed() { pressedSig(); }

		/**
		 * @return Buttons label value in UTF8.
		 */
		virtual const std::string getText() const = 0;

		/**
		 * @param pText Set the button-label value in UTF8.
		 */
		virtual void setText( const std::string& pText) = 0;
	private:
	};
}

#endif /* TRIHLAV_BUTTON_IFACE_HPP_ */
