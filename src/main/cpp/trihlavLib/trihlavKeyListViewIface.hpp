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
#ifndef TRIHLAV_I_KEY_LIST_VIEW_IFACE_HPP_
#define TRIHLAV_I_KEY_LIST_VIEW_IFACE_HPP_

#include <list>
#include <boost/signals2.hpp>
#include <tuple>

#include "trihlavViewIface.hpp"

namespace trihlav {

    class ButtonIface;

    class YubikoOtpKeyConfig;

/**
 * Interface of the key list UI.
 */
    class KeyListViewIface : virtual public ViewIface {
    public:

        typedef std::tuple<int, std::string, std::string, std::string, int, int> KeyRow_t;

        /**
         * Should be fired by the UI when user selects a row. The ids of the rows are passed.
         */
        boost::signals2::signal<void(int)> selectionChangedSig;

        /// @brief add a new key
        virtual ButtonIface &getBtnAddKey() =0;

        /// @brief Delete key accessor
        virtual ButtonIface &getBtnDelKey() =0;

        /// @brief Edit current key button accessor
        virtual ButtonIface &getBtnEditKey() =0;

        /// @brief Reload the key list.
        virtual ButtonIface &getBtnReload() =0;

        /// @brief Unselect all keys in the list
        virtual void unselectAll()=0;

        /// @brief remove all items from the list
        virtual void clear()=0;

        /// @brief add a row/key to the list
        virtual void addRow(const KeyRow_t &pRow)=0;

        /// @brief get an row identified by an id
        virtual const KeyRow_t &getRow(int pId) const =0;

        /**
         * @brief will be called by the presenter when
         * all keys has been added.
         */
        virtual void addedAllRows()=0;

        KeyRow_t createRow(int pRowIdx,
                           const YubikoOtpKeyConfig &pFromKey) const;
    };

} /* namespace trihlav */

#endif /* TRIHLAV_I_KEY_LIST_VIEW_IFACE_HPP_ */
