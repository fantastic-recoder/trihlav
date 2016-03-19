/*
 * trihlavKeyManager.cpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#include <string>
#include <iostream>
#include <stdexcept>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#if defined _WIN32 || defined _WIN64
#include <windows.h>
#include <stdio.h>
#include <lmcons.h>
#endif

#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavFailedCreateConfigDir.hpp"
#include "trihlavLib/trihlavCannotWriteConfigDir.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"

using std::string;
using boost::filesystem::path;
using boost::filesystem::recursive_directory_iterator;
using boost::filesystem::perms;
using boost::regex_match;
using boost::format;

namespace trihlav {

using YubikoOtpKeyConfigPtr= std::shared_ptr<YubikoOtpKeyConfig>;

/**
 *  @param pConfigDir The directory where to store the key configuration data.
 */
KeyManager::KeyManager(const path& pConfigDir) :
		itsInitializedFlag(false), itsConfigDir(pConfigDir) {
	BOOST_LOG_NAMED_SCOPE("KeyManager::KeyManager");
	BOOST_LOG_TRIVIAL(debug)<< "C'tor from config. dir. OK: "<< itsConfigDir << ".";
}

KeyManager::KeyManager() :
		itsInitializedFlag(false), itsConfigDir(detectConfigDir()) {
	BOOST_LOG_NAMED_SCOPE("KeyManager::KeyManager1");
	BOOST_LOG_TRIVIAL(debug)<< "C'tor from config dir ok: "<< itsConfigDir << ".";
}

/**
 * If the internal resources will be initialized in case they are not yet
 * initialized.
 * ,
 * @return (getter) current connection directory.
 */
const path&
KeyManager::getConfigDir() const {
	BOOST_LOG_NAMED_SCOPE("KeyManager::getConfigDir()");
	if (!isInitialized()) {
		BOOST_LOG_TRIVIAL(debug)<< "Checking config dir " << itsConfigDir << ".";
		if(exists(itsConfigDir)) {
			const perms &myPerms = status(itsConfigDir).permissions();
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
			BOOST_LOG_TRIVIAL(debug)<< "Home: " << myHome<<".";
	return myHome;
}

#if defined _WIN32 || defined _WIN64

/**

 This function checks the token of the calling thread to see if the caller
 belongs to the Administrators group.

 @return
 TRUE if the caller is an administrator on the local machine.
 Otherwise, FALSE.
 */
bool isCurrentUserLocalAdministrator(void)
{
	BOOL fReturn = FALSE;
	DWORD dwStatus;
	DWORD dwAccessMask;
	DWORD dwAccessDesired;
	DWORD dwACLSize;
	DWORD dwStructureSize = sizeof(PRIVILEGE_SET);
	PACL pACL = NULL;
	PSID psidAdmin = NULL;

	HANDLE hToken = NULL;
	HANDLE hImpersonationToken = NULL;

	PRIVILEGE_SET ps;
	GENERIC_MAPPING GenericMapping;

	PSECURITY_DESCRIPTOR psdAdmin = NULL;
	SID_IDENTIFIER_AUTHORITY SystemSidAuthority = SECURITY_NT_AUTHORITY;

	/*
	 Determine if the current thread is running as a user that is a member of
	 the local admins group.  To do this, create a security descriptor that
	 has a DACL which has an ACE that allows only local aministrators access.
	 Then, call AccessCheck with the current thread's token and the security
	 descriptor.  It will say whether the user could access an object if it
	 had that security descriptor.  Note: you do not need to actually create
	 the object.  Just checking access against the security descriptor

	 alone
	 will be sufficient.
	 */
	const DWORD ACCESS_READ = 1;
	const DWORD ACCESS_WRITE = 2;

	__try
	{

		/*
		 AccessCheck() requires an impersonation token.  We first get a primary
		 token and then create a duplicate impersonation token.  The
		 impersonation token is not actually assigned to the thread, but is
		 used in the call to AccessCheck.  Thus, this function itself never
		 impersonates, but does use the identity of the thread.  If the thread
		 was impersonating already, this function uses that impersonation context.
		 */
		if (!OpenThreadToken(GetCurrentThread(), TOKEN_DUPLICATE|TOKEN_QUERY,

						TRUE, &hToken))
		{
			if (GetLastError() != ERROR_NO_TOKEN)
			__leave;

			if (!OpenProcessToken(GetCurrentProcess(),

							TOKEN_DUPLICATE|TOKEN_QUERY, &hToken))
			__leave;
		}

		if (!DuplicateToken (hToken, SecurityImpersonation,

						&hImpersonationToken))
		__leave;

		/*
		 Create the binary representation of the well-known SID that
		 represents the local administrators group.  Then create the security
		 descriptor and DACL with an ACE that allows only local admins access.
		 After that, perform the access check.  This will determine whether
		 the current user is a local admin.
		 */
		if (!AllocateAndInitializeSid(&SystemSidAuthority, 2,
						SECURITY_BUILTIN_DOMAIN_RID,
						DOMAIN_ALIAS_RID_ADMINS,
						0, 0, 0, 0, 0, 0, &psidAdmin))
		__leave;

		psdAdmin = LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
		if (psdAdmin == NULL)
		__leave;

		if (!InitializeSecurityDescriptor(psdAdmin,

						SECURITY_DESCRIPTOR_REVISION))
		__leave;

		// Compute size needed for the ACL.
		dwACLSize = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) +
		GetLengthSid(psidAdmin) - sizeof(DWORD);

		pACL = (PACL)LocalAlloc(LPTR, dwACLSize);
		if (pACL == NULL)
		__leave;

		if (!InitializeAcl(pACL, dwACLSize, ACL_REVISION2))
		__leave;

		dwAccessMask= ACCESS_READ | ACCESS_WRITE;

		if (!AddAccessAllowedAce(pACL, ACL_REVISION2, dwAccessMask,

						psidAdmin))
		__leave;

		if (!SetSecurityDescriptorDacl(psdAdmin, TRUE, pACL, FALSE))
		__leave;

		/*
		 AccessCheck validates a security descriptor somewhat; set the group
		 and owner so that enough of the security descriptor is filled out to
		 make AccessCheck happy.
		 */
		SetSecurityDescriptorGroup(psdAdmin, psidAdmin, FALSE);
		SetSecurityDescriptorOwner(psdAdmin, psidAdmin, FALSE);

		if (!IsValidSecurityDescriptor(psdAdmin))
		__leave;

		dwAccessDesired = ACCESS_READ;

		/*
		 Initialize GenericMapping structure even though you
		 do not use generic rights.
		 */
		GenericMapping.GenericRead = ACCESS_READ;
		GenericMapping.GenericWrite = ACCESS_WRITE;
		GenericMapping.GenericExecute = 0;
		GenericMapping.GenericAll = ACCESS_READ | ACCESS_WRITE;

		if (!AccessCheck(psdAdmin, hImpersonationToken, dwAccessDesired,
						&GenericMapping, &ps, &dwStructureSize, &dwStatus,
						&fReturn))
		{
			fReturn = FALSE;
			__leave;
		}
	}
	__finally
	{
		// Clean up.
		if (pACL) LocalFree(pACL);
		if (psdAdmin) LocalFree(psdAdmin);
		if (psidAdmin) FreeSid(psidAdmin);
		if (hImpersonationToken) CloseHandle (hImpersonationToken);
		if (hToken) CloseHandle (hToken);
	}

	return (fReturn==TRUE);
}
#endif

void KeyManager::checkPath(const path& pPath, bool &readable,
		bool &writable) const {
	BOOST_LOG_NAMED_SCOPE("KeyManager::checkPath()");
	path filePath = pPath / "test.txt";

	// remove a possibly existing test file
	remove(filePath);

	// check that the path exists
	if (!is_directory(pPath)) {
		readable = writable = false;
		return;
	}

	// try to write in the location
	std::ofstream outfile(filePath.native());
	outfile << "I can write!" << std::endl;
	outfile.close();

	if (!outfile.fail() && !outfile.bad()) {
		writable = true;
	}

	// look for a file to read
	std::ifstream::pos_type size;
	char * memblock;
	for (auto it = recursive_directory_iterator(pPath);
			it != recursive_directory_iterator(); it++) {
		if (!is_directory(it->path())) {
			std::string sFilePath = it->path().native();
			std::ifstream file(sFilePath.c_str(),
					std::ios::in | std::ios::binary | std::ios::ate);
			if (file.is_open()) {
				size = file.tellg();
				if (size > 0) {
					memblock = new char[1];
					file.seekg(0, std::ios::beg);
					file.read(memblock, 1);
					file.close();
					delete[] memblock;
					if (!file.fail() && !file.bad()) {
						readable = true;
					}
					break;
				}
			} else {
				// there is a non readable file in the folder
				// readable = false;
				break;
			}
		}
	}

	// delete the test file
	remove(filePath);
}

const path KeyManager::detectConfigDir() const {
	BOOST_LOG_NAMED_SCOPE("KeyManager::detectConfigDir()");
	// try to open
	path myDefPath("/etc/trihlav/keys");
	bool myWriteable, myReadable;
	checkPath(myDefPath, myWriteable, myReadable);
	if (myWriteable) {
		BOOST_LOG_TRIVIAL(debug)<< ": "<< myDefPath << " is writable.";
	} else {
		myDefPath=(((getHome() / ".config")/ "trihlav") / "keys");
		create_directories(myDefPath);
		checkPath(myDefPath,myWriteable,myReadable);
		if(myWriteable) {
			BOOST_LOG_TRIVIAL(debug)<< ": "<< myDefPath << " is writable.";
		} else {
			throw new FailedCreateConfigDir(itsConfigDir);
		}
	}
	return myDefPath;
}

/**
 * @param pConfigDir configuration directory.
 */
void KeyManager::setConfigDir(const path& pConfigDir) {
	BOOST_LOG_NAMED_SCOPE("KeyManager::setConfigDir");
	bool myReadable = false, myWriteable = false;
	checkPath(pConfigDir, myReadable, myWriteable);
	if (myWriteable) {
		BOOST_LOG_TRIVIAL(debug)<< ": "<< pConfigDir << " is writable.";
	} else {
		throw new FailedCreateConfigDir(itsConfigDir);
	}
	itsConfigDir = pConfigDir;
}

const boost::regex K_KEY_FILTER(".*\\.trihlav-key\\.json");

/**
 * @return the loaded keys count.
 */
size_t KeyManager::loadKeys() {
	BOOST_LOG_NAMED_SCOPE("KeyManager::loadKeys");
	itsKeyList.resize(0);
	itsKeyMapByPublicId.clear();
	for (auto it = recursive_directory_iterator(getConfigDir());
			it != recursive_directory_iterator(); it++) {
		boost::smatch matchProd;
		const path myFName(it->path().native());
		BOOST_LOG_TRIVIAL(debug)<< "Found key file " << myFName << ".";
		if (!is_directory(it->path())
				&& regex_match(myFName.string(), matchProd, K_KEY_FILTER)) {
			YubikoOtpKeyConfig* myCfg = new YubikoOtpKeyConfig(*this, myFName);
			myCfg->load();
			YubikoOtpKeyConfigPtr myKey { myCfg };
			itsKeyList.emplace_back(myKey);
			string myId(myKey->getPublicId());
			if (myId.empty()) {
				(myId += "generated:") += myKey->getFilename().string();
			}
			itsKeyMapByPublicId.emplace(KeyMap_t::value_type { myId, myKey });
		}
	}
	return itsKeyList.size();
}

const size_t KeyManager::getKeyCount() const {
	return itsKeyList.size();
}

const YubikoOtpKeyConfig& KeyManager::getKey(const size_t pIdx) const {
	if (pIdx < 0 || itsKeyList.size() < pIdx) {
		throw new std::range_error(
				(format("Key index %1% is out of range <0,%2%>.") % pIdx
						% itsKeyList.size()).str());
	}
	return *(itsKeyList[pIdx]);
}

/**
 * @param pPubId modhex encoded public id prefix.
 */
const YubikoOtpKeyConfig* KeyManager::getKeyByPublicId(
		const string& pPubId) const {
	BOOST_LOG_NAMED_SCOPE("KeyManager::getKeyByPublicId const");
	auto myKey=itsKeyMapByPublicId.find(pPubId);
	if (myKey == itsKeyMapByPublicId.end()) {
		BOOST_LOG_TRIVIAL(warning)<< "Key prefixed " << pPubId << " has not been found.";
		return 0;
	}
	return myKey->second.get();
}

/**
 * @see getKeyByPublicId(const string& pPubId) const
 */
YubikoOtpKeyConfig* KeyManager::getKeyByPublicId(const string& pPubId) {
	BOOST_LOG_NAMED_SCOPE("KeyManager::getKeyByPublicId");
	auto myKey=itsKeyMapByPublicId.find(pPubId);
	if (myKey == itsKeyMapByPublicId.end()) {
		BOOST_LOG_TRIVIAL(warning)<< "Key prefixed " << pPubId << " has not been found.";
		return 0;
	}
	return myKey->second.get();
}

void KeyManager::update(const std::string& pPubId, YubikoOtpKeyConfig& pKey) {
	if(!pPubId.empty()) {
		const auto myIt=itsKeyMapByPublicId.find(pPubId);
		if( myIt != itsKeyMapByPublicId.end()) {
			YubikoOtpKeyConfigPtr myFoundKey=myIt->second;
			if(myFoundKey->getPrivateId().compare(pKey.getPrivateId())==0) {
				itsKeyMapByPublicId.erase(myIt);
			}
		} else {
			BOOST_LOG_TRIVIAL(debug) << "Public id " << pPubId << " has not been found.";
		}
		itsKeyMapByPublicId[pKey.getPublicId()]= YubikoOtpKeyConfigPtr{&pKey};
	} else {
		BOOST_LOG_TRIVIAL(debug) << "Public id is empty.";
	}
}

}

/* namespace trihlav */
