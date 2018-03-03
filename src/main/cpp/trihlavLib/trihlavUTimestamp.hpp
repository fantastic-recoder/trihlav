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

#ifndef YUSERLIB_YUSERTIMESTAMP_HPP_
#define YUSERLIB_YUSERTIMESTAMP_HPP_

#include <yubikey.h>

namespace trihlav {

    /**
     * Allow easier acces to Yubikeys timestamp.
     */
    union UTimestamp {
        /** Low/high access as in Yubkeys struct. */
        struct {
            /** Fill the struct to 32 bit */
            uint8_t filler;
            /** Timestamp (high part). */
            uint8_t tstph;
            /** Timestamp incremented by approx 8Hz (low part). */
            uint16_t tstpl;
        } tstp;
        /** Access timestamp as an integer. */
        unsigned int tstp_int;

        UTimestamp() : tstp_int(0) {}

        UTimestamp(const int pAsInt) : tstp_int(pAsInt) {}
    };

} // end namespace yuSerApi


#endif /* YUSERLIB_YUSERTIMESTAMP_HPP_ */
