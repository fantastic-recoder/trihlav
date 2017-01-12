//
// Created by grobap on 10.01.17.
//

#ifndef TRIHLAV_WT_AUTH_RESOURCE_HPP_
#define TRIHLAV_WT_AUTH_RESOURCE_HPP_

#include <Wt/WResource>

namespace trihlav {

    /**
     * Authenticate an "one time password" (OTP) as a REST API call.
     */
    class WtAuthResource : public Wt::WResource {
    public:
        virtual ~WtAuthResource();

    protected:
        virtual void handleRequest(const Wt::Http::Request &pRequest, Wt::Http::Response &pResponse);
    };

}

#endif //TRIHLAV_WT_AUTH_RESOURCE_HPP_
