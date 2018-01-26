//
// Created by grobap on 10.01.17.
//

#include <string>

#include <Wt/WResource.h>
#include <Wt/Http/Response.h>

#include "trihlavWtAuthResource.hpp"

#include "trihlavLib/trihlavConstants.hpp"
#include "trihlavLib/trihlavLogApi.hpp"

using std::string;
using std::vector;
using Wt::WResource;
using Wt::Http::Request;
using Wt::Http::Response;

namespace trihlav {

    /**
     * Reimplement the parents main action. The password request parameter can have up to 3 values (OTP passwords).
     * @param pRequest incoming - has login and password parameters.
     * @param pResponse outgoing - return "ok" on success.
     */
    void WtAuthResource::handleRequest(const Wt::Http::Request &pRequest, Wt::Http::Response &pResponse) {
        BOOST_LOG_NAMED_SCOPE("WtAuthResource::handleRequest");
        const Wt::Http::ParameterValues &myLoginVals = pRequest.getParameterValues(K_LOGIN);
        const Wt::Http::ParameterValues &myOtpVals = pRequest.getParameterValues(K_PSWD);
        string myLogin;
        vector<string> myOtp;
        if(myLoginVals.size()==1) {
            myLogin=myLoginVals[0];
        }
        BOOST_LOG_TRIVIAL(debug) << "login " << myLogin;
        if(myOtpVals.size()>=1) {
            myOtp.push_back(myOtpVals[0]);
            BOOST_LOG_TRIVIAL(debug) << "otp[0] " << myOtp[0];
        }
        if(myOtpVals.size()>=2) {
            myOtp.push_back(myOtpVals[1]);
            BOOST_LOG_TRIVIAL(debug) << "otp[1] " << myOtp[1];
        }
        if(myOtpVals.size()>=3) {
            myOtp.push_back(myOtpVals[2]);
            BOOST_LOG_TRIVIAL(debug) << "otp[2] " << myOtp[2];
        }
        pResponse.out() << "Fail!\n";
    }

}
