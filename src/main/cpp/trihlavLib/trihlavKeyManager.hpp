/*
 * trihlavKeyManager.hpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#ifndef TRIHLAVKEYMANAGER_HPP_
#define TRIHLAVKEYMANAGER_HPP_

#include <boost/filesystem.hpp>

namespace trihlavApi {

class KeyManager {
public:
	KeyManager(const boost::filesystem::path& pDir);
	virtual ~KeyManager();
};

} /* namespace trihlav */

#endif /* TRIHLAVKEYMANAGER_HPP_ */
