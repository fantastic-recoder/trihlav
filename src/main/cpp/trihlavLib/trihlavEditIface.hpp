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
#ifndef TRIHLAV_EDIT_IFACE_HPP_
#define TRIHLAV_EDIT_IFACE_HPP_

#include <string>
#include <boost/utility.hpp>

namespace trihlav {

/**
 * Interface to a UI widget, which can edit, set and get a value.
 */
template< typename T>
class EditIface : virtual public boost::noncopyable {
public:
	/**
	 * @return The edited value.
	 */
	virtual const T getValue() const = 0;

	/**
	 * @param pVal set the value, which can be edited.
	 */
	virtual void setValue(const T& pVal) =0;

	/**
	 * Set the focus in widgets editor.
	 */
	virtual void setFocus(bool) = 0;

	/// Just ensure virtual destructor.
	virtual ~EditIface(){}
};

struct StrEditIface: virtual public EditIface<std::string>{};

} /* namespace trihlav */

#endif /* TRIHLAV_EDIT_IFACE_HPP_ */
