/*
 * trihlavOsIface.hpp
 *
 *  Created on: Jul 27, 2016
 *      Author: grobap
 */

#ifndef TRIHLAV_OSIFACE_HPP_
#define TRIHLAV_OSIFACE_HPP_

#include <string>
#include <vector>
#include <iostream>

namespace trihlav {

/**
 * The operating system user information will be returned in this
 * structure.
 */
struct SysUser {
	std::string itsLogin;
	std::string itsFullName;
	const std::string str() const { return itsLogin+" [ " + itsFullName + " ]"; }
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
	virtual const SysUsers getSysUsers() const;

	/// We not need it yet, but we are prepared ...
	virtual ~OsIface();

private:
	constexpr static const char* K_ETC_PASSWD = "/etc/passwd";
};

} /* namespace trihlav */

#endif /* TRIHLAV_OSIFACE_HPP_ */
