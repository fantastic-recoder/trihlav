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

#ifndef TRIHLAV_DIALOG_VIEW_IFACE_HPP_
#define TRIHLAV_DIALOG_VIEW_IFACE_HPP_

#include <boost/signals2.hpp>

#include "trihlavLib/trihlavViewIface.hpp"

namespace trihlav {

class ButtonIface;

/**
 * @brief Interface common to all UI dialogues with ok/cancel functionality.
 */
class DialogViewIface: public virtual ViewIface {

public:

    typedef ::boost::signals2::signal<void(const bool)> SigDialogFinished ;

    SigDialogFinished sigDialogFinished;

    /// @brief Cancel button constant interface.
	virtual const ButtonIface&  getBtnCancel() const = 0;

	/// @brief Cancel button interface.
	virtual ButtonIface&  getBtnCancel() = 0;

	/// @brief ok button constant interface.
	virtual const ButtonIface&  getBtnOk() const = 0;

	/// @brief ok button interface.
	virtual ButtonIface&  getBtnOk() = 0;

	/// @brief Shortcut to set ok button label
	virtual void setOkLabel( const std::string& pNewLabel);

    /// @brief Show the dialog.
    virtual void show() = 0;

    virtual ~DialogViewIface();
};

} /* namespace trihlav */

#endif /* TRIHLAV_DIALOG_VIEW_IFACE_HPP_ */
