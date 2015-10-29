/*
 * trihlavKeyManager.cpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#include "trihlavKeyManager.hpp"

namespace trihlavApi {

/**
 *  @param pDir The directory where to store the key configuration data.
 */
KeyManager::KeyManager(const boost::filesystem::path& pDir) :
		itsInitializedFlag(false),
		itsConfigDir(pDir) {

	// TODO Auto-generated constructor stub

}

KeyManager::~KeyManager() {
	// TODO Auto-generated destructor stub
}

} /* namespace trihlav */
