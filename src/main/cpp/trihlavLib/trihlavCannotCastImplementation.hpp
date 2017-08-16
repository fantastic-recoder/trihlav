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

#ifndef TRIHLAV_CANNOT_CAST_IMPLEMENTATION_HPP_
#define TRIHLAV_CANNOT_CAST_IMPLEMENTATION_HPP_

#include <stdexcept>

namespace trihlav {

    class CannotCastImplementation  : virtual public std::invalid_argument {
    private:
        std::string m_Typename;
        std::string m_Msg;
    public:
        const std::string &getTypename() const {
            return m_Typename;
        }

        void setTypename(const std::string &pTypename) {
            m_Typename = pTypename;
        }
        const char* what() const throw();
    public:
        CannotCastImplementation(const std::string& pTypename);
    };

}

#endif //TRIHLAV_CANNOT_CAST_IMPLEMENTATION_HPP_
