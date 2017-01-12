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

#ifndef TRIHLAV_SETTINGS_HPP_
#define TRIHLAV_SETTINGS_HPP_

#include <string>
#include <boost/filesystem.hpp>

namespace trihlav {

    /**
     * Global settings.
     */
    class Settings {
    public:

        Settings();

        Settings(const boost::filesystem::path &pConfigDir);

        /**
         * Allow superuser?
         * @return Settings#itsAllowRoot.
         */
        bool isAllowRoot() const {
            return itsAllowRoot;
        }

        /**
         * Allow superuser?
         * @return Settings#itsAllowRoot.
         */
        bool& isAllowRoot() {
            return itsAllowRoot;
        }

        /**
         * On UNIX systems will allow select user from this value.
         * @return Settings#itsMinUser .
         */
        int getMinUser() const {
            return itsMinUser;
        }

        /**
         * On UNIX systems will allow select user from this value.
         * @return Settings#itsMinUser .
         */
        int& getMinUser() {
            return itsMinUser;
        }

        void save();

        /// @brief Load settings from disk, when they exists.
        bool load();

        const boost::filesystem::path &getConfigDir() const;

        void setConfigDir(const boost::filesystem::path &pPath);

        /// @brief Get users home directory
        static const boost::filesystem::path getHome();

        /**
         * Are all internal resources ready.
         */
        const bool isInitialized() const {
            return itsInitializedFlag;
        }


    private:
        boost::filesystem::path itsArchFilename;

        bool itsAllowRoot=true;
        int  itsMinUser=1000;

        boost::filesystem::path itsConfigDir;
        mutable bool itsInitializedFlag;

        const boost::filesystem::path detectConfigDir() const;

        void checkPath(const boost::filesystem::path &pPath, bool &readable, bool &writable) const;
    };
}


#endif //TRIHLAV_SETTINGS_HPP_
