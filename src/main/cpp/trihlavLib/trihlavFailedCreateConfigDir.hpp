//
// Created by grobap on 05.11.15.
//

#ifndef TRIHLAV_FAILEDCREATECONFIGDIR_HPP_
#define TRIHLAV_FAILEDCREATECONFIGDIR_HPP_

#include <stdexcept>
#include <boost/filesystem/path.hpp>

namespace trihlav {

    class FailedCreateConfigDir  : virtual public std::invalid_argument {
    private:
        boost::filesystem::path m_ConfigDir;
        std::string             m_Msg;
    public:
        const boost::filesystem::path &getConfigDir() const {
            return m_ConfigDir;
        }

        void setConfigDir(const boost::filesystem::path &pConfigDir) {
            m_ConfigDir = pConfigDir;
        }
        const char* what() const throw();
    public:
        FailedCreateConfigDir(const boost::filesystem::path& pConfigDir);
    };

}

#endif //TRIHLAVSRV_FAILEDCREATECONFIGDIR_H
