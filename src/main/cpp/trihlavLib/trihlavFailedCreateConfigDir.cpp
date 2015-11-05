//
// Created by grobap on 05.11.15.
//

#include <string>

#include "trihlavFailedCreateConfigDir.hpp"

namespace {
    static const std::string K_FAILED_CREATE_CONFIG_DIR("Failed to create config directory.");
    static const std::string K_FAILED_FORMAT_MSG("Failed to format the error message.");
}

namespace trihlavApi {
    using namespace std;

    FailedCreateConfigDir::FailedCreateConfigDir(const boost::filesystem::path &pConfigDir) : invalid_argument(
            K_FAILED_CREATE_CONFIG_DIR.c_str()) {
        try {
            itsMsg=string("Failed to create config directory \"")
                   + getConfigDir().native()
                   + string("\"") ;
        } catch (...) {
            itsMsg=K_FAILED_FORMAT_MSG.c_str();
        }
    }

    const char* FailedCreateConfigDir::what() const throw() {
        return itsMsg.c_str();
    }


}
