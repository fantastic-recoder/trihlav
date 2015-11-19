//
// Created by grobap on 05.11.15.
//

#ifndef TRIHLAV_CANNOTWRITECONFIGDIR_HPP_
#define TRIHLAV_CANNOTWRITECONFIGDIR_HPP_

#include <stdexcept>
#include <boost/filesystem/path.hpp>

namespace trihlav {

    class CannotWriteConfigDir  : virtual public std::invalid_argument {
    private:
        boost::filesystem::path itsConfigDir;
        std::string             itsMsg;
    public:
        const boost::filesystem::path &getConfigDir() const {
            return itsConfigDir;
        }

        void setConfigDir(const boost::filesystem::path &pConfigDir) {
            itsConfigDir = pConfigDir;
        }
        const char* what() const throw();
    public:
        CannotWriteConfigDir(const boost::filesystem::path& pConfigDir);
    };

}

#endif //TRIHLAV_CANNOTWRITECONFIGDIR_HPP_
