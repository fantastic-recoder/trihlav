/*
 * trihlavOsIface.hpp
 *
 *  Created on: Jul 27, 2016
 *      Author: grobap
 */

#ifndef TRIHLAV_OSIFACE_HPP_
#define TRIHLAV_OSIFACE_HPP_

#include <string>

namespace trihlav {

class OsIface {
public:
	/// Uses PAM on Linux to auth the user
	virtual bool checkOsPswd(const std::string& p_strUName, const std::string& p_strPswd);
};

} /* namespace trihlav */

#endif /* TRIHLAV_OSIFACE_HPP_ */
