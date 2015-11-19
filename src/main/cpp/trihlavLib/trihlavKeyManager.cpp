/*
 * trihlavKeyManager.cpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavKeyManager.hpp"
#include "trihlavFailedCreateConfigDir.hpp"
#include "trihlavCannotWriteConfigDir.hpp"

using namespace boost::filesystem;

namespace trihlav {

/**
 *  @param pDir The directory where to store the key configuration data.
 */
KeyManager::KeyManager(const boost::filesystem::path& pDir) :
		itsInitializedFlag(false), itsConfigDir(pDir) {
	BOOST_LOG_NAMED_SCOPE("KeyManager::KeyManager");
	BOOST_LOG_TRIVIAL(debug)<< "C'tor from config directory is ok config dir: "<< itsConfigDir << ".";
}

/**
 * If the internal resources will be initialized in case they are not yet
 * initialized.
 * ,
 * @return (getter) current connection directory.
 */
const boost::filesystem::path&
KeyManager::getConfigDir() {
	BOOST_LOG_NAMED_SCOPE("KeyManager::getConfigDir()");
	if (!isInitialized()) {
		BOOST_LOG_TRIVIAL(debug)<< "Checking config dir " << itsConfigDir << ".";
		if(exists(itsConfigDir)) {
			const perms &myPerms = status(getConfigDir()).permissions();
			if(!myPerms & perms::owner_write) {
				throw new CannotWriteConfigDir(itsConfigDir);
			}
		} else {
			BOOST_LOG_TRIVIAL(debug)<< "Creating config dir " << itsConfigDir << ".";
			if(!create_directories(itsConfigDir)) {
				throw new FailedCreateConfigDir(itsConfigDir);
			}
		}
		itsInitializedFlag=true;
	} else {
		BOOST_LOG_TRIVIAL(debug)<< "Config dir was already initialized.";
	}
	return itsConfigDir;
}

KeyManager::~KeyManager() {
	// TODO Auto-generated destructor stub
}

} /* namespace trihlav */
