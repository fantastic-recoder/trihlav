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
        CannotWriteConfigDir(const boost::filesystem::path& pConfigDir);
    };

}

#endif //TRIHLAV_CANNOTWRITECONFIGDIR_HPP_
