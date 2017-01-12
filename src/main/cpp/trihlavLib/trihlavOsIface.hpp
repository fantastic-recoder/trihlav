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

#ifndef TRIHLAV_OSIFACE_HPP_
#define TRIHLAV_OSIFACE_HPP_

#include <string>
#include <vector>
#include <iostream>

namespace trihlav {

class Settings;

/**
 * The operating system user information will be returned in this
 * structure.
 */
struct SysUser {
	std::string itsLogin;
	std::string itsFullName;
	long itsId;
	const std::string str() const { return itsLogin+" [ " + itsFullName + ", "+std::to_string(itsId) +" ]"; }
};

inline std::ostream& operator << ( std::ostream& pOstr, const SysUser& pUser )  {
	pOstr << "SysUser{ login=\"" << pUser.itsLogin << "\" name=\"" << pUser.itsFullName << "\" }";
	return pOstr;
}

using SysUsers = std::vector<SysUser>;

class OsIface {
public:
	/// Uses PAM on Linux to auth the user
	virtual bool checkOsPswd(const std::string& p_strUName,
			const std::string& p_strPswd) const;

	/// Execute a programm and pass a parameter
	virtual int execute(const std::string& p_strPathFilename,
			const std::string& p_strP0)const ;

	/// @brief Get all users from the operating system.
	virtual const SysUsers getSysUsers(const Settings& pSettings) const;

	/// We not need it yet, but we are prepared ...
	virtual ~OsIface();

private:
	constexpr static const char* K_ETC_PASSWD = "/etc/passwd";
};

} /* namespace trihlav */

#endif /* TRIHLAV_OSIFACE_HPP_ */
