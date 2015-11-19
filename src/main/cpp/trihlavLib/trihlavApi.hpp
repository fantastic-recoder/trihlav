#ifndef TRIHLAV_API_HPP
#define TRIHLAV_API_HPP

#include <string>

namespace trihlav {

class YubikoOtpKeyConfig;

    /// Check the passed OTP password
    bool check(const std::string& pPasswd);

    /// Get the yubiko server configuration
    YubikoOtpKeyConfig& getConfig();

}

#endif // TRIHLAV_API_HPP
