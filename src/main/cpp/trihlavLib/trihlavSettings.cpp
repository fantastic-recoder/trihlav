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

#include <fstream>
// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "trihlavSettings.hpp"

namespace boost {
    namespace serialization {

        template<class Archive>
        void serialize(Archive &pArch, trihlav::Settings &pSettings, const unsigned int pVersion) {
            pArch & pSettings.getMinUser();
            pArch & pSettings.isAllowRoot();
        }

    } // namespace serialization
} // namespace boost

void trihlav::Settings::load() {

    // create and open an archive for input
    std::ifstream myIfs(itsArchFilename.native());
    boost::archive::text_iarchive myIa(myIfs);
    // read class state from archive
    myIa >> (*this);
    // archive and stream closed when destructors are called
}

void trihlav::Settings::save() {
    // create and open a character archive for output
    std::ofstream myOfs(itsArchFilename.native());
    boost::archive::text_oarchive myOa(myOfs);
    // write class instance to archive
    myOa << (*this);
    // archive and stream closed when destructors are called
}

trihlav::Settings::Settings(const boost::filesystem::path&  pArchFilename) ://
        itsArchFilename(pArchFilename) {

}

