/*
 * trihlavOsIface.cpp
 *
 *  Created on: Jul 27, 2016
 *      Author: grobap
 */

#include <stdio.h>
#include <security/pam_appl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavLib/trihlavOsIface.hpp"

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

bool OsIface::checkOsPswd(const string& p_strUName, const string& p_strPswd) {
	BOOST_LOG_NAMED_SCOPE("OsIface::checkOsPswd");

	const struct pam_conv local_conversation = { function_conversation, NULL };
	pam_handle_t *local_auth_handle = NULL; // this gets set by pam_start

	int aRetVal;
//	aRetVal = pam_start("common-auth", p_strUName.c_str(), NULL, &local_auth_handle);
	aRetVal = pam_start("common-auth", p_strUName.c_str(), &local_conversation, &local_auth_handle);
//	pam_set_item( local_auth_handle, PAM_AUTHTOK, p_strPswd.c_str());
	if (aRetVal != PAM_SUCCESS) {
		BOOST_LOG_TRIVIAL(info) << "pam_start returned: " << aRetVal << " for user " << p_strUName;
		return false;
	}

	myReply = (struct pam_response *) malloc(sizeof(struct pam_response));

	myReply[0].resp = strdup(p_strPswd.c_str());
	myReply[0].resp_retcode = 0;
	aRetVal = pam_authenticate(local_auth_handle, 0);

	if (aRetVal != PAM_SUCCESS) {
		if (aRetVal == PAM_AUTH_ERR) {
			BOOST_LOG_TRIVIAL(info) << "Authentication failure for user " << p_strUName;
		} else {
			BOOST_LOG_TRIVIAL(info) << "pam_authenticate returned: " << aRetVal << " for user " << p_strUName;
		}
		return false;
	}
	BOOST_LOG_TRIVIAL(info) << "Authenticated user " << p_strUName;

	aRetVal = pam_end(local_auth_handle, aRetVal);

	if (aRetVal != PAM_SUCCESS) {
		BOOST_LOG_TRIVIAL(info) << "pam_authenticate returned: " << aRetVal << " for user " << p_strUName;
		return false;
	}

	return true;
}

} /* namespace trihlav */
