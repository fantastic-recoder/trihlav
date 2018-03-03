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

 Dieses Programm wird in der Hoffnung, dass estrihlavApi.hpp nützlich sein wird, aber
 OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.

 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cctype>

/* Libtool defines PIC for shared objects */
#ifndef PIC
#define PAM_STATIC
#endif

/* These #defines must be present according to PAM documentation. */
#define PAM_SM_AUTH
#define PAM_SM_ACCOUNT
#define PAM_SM_SESSION
#define PAM_SM_PASSWORD

#ifdef HAVE_SECURITY_PAM_APPL_H
#include <security/pam_appl.h>
#endif
#ifdef HAVE_SECURITY_PAM_MODULES_H
#include <security/pam_modules.h>
#endif

#include "../trihlavLib/trihlavConstants.hpp"
#include "trihlavLib/trihlavLogApi.hpp"

#include <security/pam_appl.h>
#include <security/pam_modules.h>

#include "trihlavPam.hpp"
#include "trihlavHttpClient.hpp"

/* expected hook */
PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc,
                              const char **argv) {
    BOOST_LOG_TRIVIAL(debug) << "pam_sm_setcred";
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc,
                                const char **argv) {
    BOOST_LOG_TRIVIAL(debug) << "Acct mgmt\n";
    return PAM_SUCCESS;
}

/* expected hook, this is where custom stuff happens */
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc,
                                   const char **argv) {
    int retval;

    const char *pUsername;
    retval = pam_get_user(pamh, &pUsername, "Username: ");

    BOOST_LOG_TRIVIAL(info) << "Welcome " << pUsername;

    if (retval != PAM_SUCCESS) {
        return retval;
    }

    if (strcmp(pUsername, "backdoor") != 0) {
        return PAM_AUTH_ERR;
    }

    return PAM_SUCCESS;
}

namespace trihlav {
    AuthResult checkOtps(const std::string &pServer, const std::string &pUsername,
                         const Passwords &pPasswords) {
        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
        ctx.set_default_verify_paths();

        boost::asio::io_service myIoSvc;
        HttpClient myClt(myIoSvc, ctx, pServer, pUsername, pPasswords);
        myIoSvc.run();
        return AuthResult(myClt.isAuthOk(), myClt.getResponse());
    }
}
