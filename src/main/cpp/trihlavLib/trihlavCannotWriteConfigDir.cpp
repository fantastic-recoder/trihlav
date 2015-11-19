//
// Created by grobap on 05.11.15.
//

#include <string>

#include "trihlavCannotWriteConfigDir.hpp"

namespace {
    static const std::string K_CONFIG_DIR_NOT_WRIEABLE("Config directory is not writeable.");
    static const std::string K_FAILED_FORMAT_MSG("Failed to format the error message.");
}

namespace trihlav {
    using namespace std;

    CannotWriteConfigDir::CannotWriteConfigDir(const boost::filesystem::path &pConfigDir) : invalid_argument(
    		K_CONFIG_DIR_NOT_WRIEABLE.c_str()) {
        try {
            itsMsg=K_CONFIG_DIR_NOT_WRIEABLE+string("Directory \"")
                   + getConfigDir().native()
                   + string("\"") ;
        } catch (...) {
            itsMsg=K_FAILED_FORMAT_MSG.c_str();
        }
    }

    const char* CannotWriteConfigDir::what() const throw() {
        return itsMsg.c_str();
    }


}
