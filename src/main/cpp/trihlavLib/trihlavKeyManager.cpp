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
 *  @param pConfigDir The directory where to store the key configuration data.
 */
KeyManager::KeyManager(const boost::filesystem::path& pConfigDir) :
		itsInitializedFlag(false), itsConfigDir(pConfigDir) {
	BOOST_LOG_NAMED_SCOPE("KeyManager::KeyManager");
	BOOST_LOG_TRIVIAL(debug)<< "C'tor from config dir ok: "<< itsConfigDir << ".";
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
		BOOST_LOG_TRIVIAL(debug)<< "Config. dir. was already initialized.";
	}
	return itsConfigDir;
}

KeyManager::~KeyManager() {
	BOOST_LOG_NAMED_SCOPE("KeyManager::~KeyManager");
}

/**
 * 	the most portable way would have to be getenv("HOME")
	on Unix and concatenating the results of
*	getenv("HOMEDRIVE") and getenv("HOMEPATH") on Windows.
 *
 */
const boost::filesystem::path KeyManager::getHome() {
	BOOST_LOG_NAMED_SCOPE("KeyManager::getHome");

#ifdef TARGET_OS_MAC

#elif defined __linux__
	path myHome(getenv("HOME"));
#elif defined _WIN32 || defined _WIN64
	path myHome(string(getenv("HOMEDRIVE"))+"\\\\"+string(getenv("HOMEPATH"));
#else
#   error "unknown platform"
#endif
	BOOST_LOG_TRIVIAL(debug)<< "Home: \"" << myHome<<"\"";
	return myHome;
}

} /* namespace trihlav */
