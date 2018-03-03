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

#ifndef TRIHLAV_REC_2_STR_VISITOR_HPP_
#define TRIHLAV_REC_2_STR_VISITOR_HPP_

#include <string>
#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>

namespace trihlav {

/**
 * Control what is in the record and how it will be displayed.
 */
    class Rec2StrVisitor : public boost::static_visitor<std::string> {
    public:

        template<typename T>
        std::string operator()(T pVal) const {
            return boost::lexical_cast<std::string>(pVal);
        }
    };

}  // namespace trihlav

#endif /* TRIHLAV_REC_2_STR_VISITOR_HPP_ */
