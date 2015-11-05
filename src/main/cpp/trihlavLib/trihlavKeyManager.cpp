/*
 * trihlavKeyManager.cpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include "trihlavKeyManager.hpp"
#include "trihlavFailedCreateConfigDir.hpp"

using namespace  boost::filesystem;

namespace trihlavApi {

/**
 *  @param pDir The directory where to store the key configuration data.
 */
KeyManager::KeyManager(const boost::filesystem::path& pDir) :
		itsInitializedFlag(false),
		itsConfigDir(pDir) {
	BOOST_LOG_NAMED_SCOPE ("KeyManager::KeyManager");
}

/**
 * If the internal resources will be initialized in case they are not yet
 * initialized
 * ,
 * @return (getter) current connection directory.
 */
const boost::filesystem::path&
	KeyManager::getConfigDir() const {
        BOOST_LOG_NAMED_SCOPE("getConfigDir");
	if(!isInitialized()) {
        if(exists(getConfigDir()))  {
            const perms &myPerms = status(getConfigDir()).permissions();
            if(!myPerms & perms::owner_write){

           } else {
                if(!create_directories(getConfigDir())) {
                    throw new FailedCreateConfigDir(getConfigDir());
                }
            }
        }
	}
	return itsConfigDir;
}

KeyManager::~KeyManager() {
	// TODO Auto-generated destructor stub
}

} /* namespace trihlav */
