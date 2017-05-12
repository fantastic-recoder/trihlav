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

#include <stdio.h>
#include <security/pam_appl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#elif

#ifdef _WIN32
#include <windows.h>
#endif

#endif

#include <regex>

#include <boost/filesystem/fstream.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavLib/trihlavOsIface.hpp"
#include "trihlavLib/trihlavSettings.hpp"

using std::string;

namespace {

struct pam_response *myReply;

/// function used to get user input
int function_conversation(int num_msg, const struct pam_message **msg,
		struct pam_response **resp, void *appdata_ptr) {
	*resp = myReply;
	return PAM_SUCCESS;
}

} // end anon namespace

namespace trihlav {

bool OsIface::checkOsPswd(const string& p_strUName,
		const string& p_strPswd) const {
	BOOST_LOG_NAMED_SCOPE("OsIface::checkOsPswd");

	const struct pam_conv local_conversation = { function_conversation, NULL };
	pam_handle_t *local_auth_handle = nullptr; // this gets set by pam_start

	int aRetVal;
	aRetVal = pam_start("common-auth", p_strUName.c_str(), &local_conversation,
			&local_auth_handle);
//	pam_set_item( local_auth_handle, PAM_AUTHTOK, p_strPswd.c_str());
	if (aRetVal != PAM_SUCCESS) {
		BOOST_LOG_TRIVIAL(info)<< "pam_start returned: " << aRetVal << " for user " << p_strUName;
		return false;
	}

	myReply = (struct pam_response *) malloc(sizeof(struct pam_response));

	myReply[0].resp = strdup(p_strPswd.c_str());
	myReply[0].resp_retcode = 0;
	aRetVal = pam_authenticate(local_auth_handle, 0);

	if (aRetVal != PAM_SUCCESS) {
		if (aRetVal == PAM_AUTH_ERR) {
			BOOST_LOG_TRIVIAL(info)<< "Authentication failure for user " << p_strUName;
		} else {
			BOOST_LOG_TRIVIAL(info) << "pam_authenticate returned: " << aRetVal << " for user " << p_strUName;
		}
		return false;
	}
	BOOST_LOG_TRIVIAL(info)<< "Authenticated user " << p_strUName;

	aRetVal = pam_end(local_auth_handle, aRetVal);

	if (aRetVal != PAM_SUCCESS) {
		BOOST_LOG_TRIVIAL(info)<< "pam_authenticate returned: " << aRetVal << " for user " << p_strUName;
		return false;
	}

	return true;
}

int OsIface::execute(const std::string& p_strPathFilename,
		const std::string& p_strP0) const {
	int myRetVal = 0;
#ifdef __unix__
	pid_t pid;
	int status;
	pid_t ret;
	const char * const args[3] =
			{ p_strPathFilename.c_str(), p_strP0.c_str(), 0 };
	char **env;
	extern char **environ;

	/* ... Sanitize arguments ... */

	pid = fork();
	if (pid == -1) {
		/* Handle error */
	} else if (pid != 0) {
		while ((ret = waitpid(pid, &status, 0)) == -1) {
			if (errno != EINTR) {
				/* Handle error */
				break;
			}
		}
		if ((ret != -1) && (!WIFEXITED(status) || !WEXITSTATUS(status))) {
			/* Report unexpected child status */
		}
	} else {
		/* ... Initialize env as a sanitized copy of environ ... */
		if (execve(p_strPathFilename.c_str(), const_cast<char* const *>(args),
				env) == -1) {
			/* Handle error */
			_Exit(127);
		}
	}
#elif
#ifdef __WINDOWS__
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	if (!CreateProcess(TEXT(p_strPathFilename.c_str()), p_strP0.c_str(), NULL, NULL, FALSE,
					0, 0, 0, &si, &pi)) {
		/* Handle error */
	}
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
#endif
#endif
	return myRetVal;
}

OsIface::~OsIface() {
}

/**
 * Can consume time and IO, when needed often, cache results.
 *
 * @return The operating system users in a STL container.
 */
const SysUsers OsIface::getSysUsers(const Settings& pSettings) const {
	BOOST_LOG_NAMED_SCOPE("OsIface::getSysUsers");
	SysUsers myUsers;
#ifdef __unix__
	static const std::regex K_PSWD_LN(
			"^((#.*|[a-z\\-_0-9]*):([^:]*):([0-9]*):([0-9]*):([^:]*):(/[^:]*):(/[^:]*))$");
	boost::filesystem::ifstream myPswdFile(K_ETC_PASSWD);
	if (myPswdFile) {
		string aReadLine;
		while (getline(myPswdFile, aReadLine)) {
			std::smatch myMatches;
			if (regex_match(aReadLine, myMatches, K_PSWD_LN)) {
				SysUser myUser{myMatches[2],myMatches[6],std::stol(myMatches[4])};
				if(pSettings.getMinUser()<=myUser.itsId) {
					myUsers.push_back(myUser);
				}
			} else {
				BOOST_LOG_TRIVIAL(warning)<<"Line did not match: " << aReadLine;
			}
		}
	} else {
		BOOST_LOG_TRIVIAL(error)<<"Could not open '" << K_ETC_PASSWD << "'.";
	}
#endif
#ifdef __WINDOWS__
	BOOST_LOG_TRIVIAL(error)<<"OsIface::getSysUsers() is not yet implemented on windows.";
#endif
	return myUsers;
}


} /* namespace trihlav */
