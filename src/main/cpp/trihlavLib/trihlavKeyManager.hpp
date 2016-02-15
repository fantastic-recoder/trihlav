/*
 * trihlavKeyManager.hpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_KEY_MANAGER_HPP_
#define TRIHLAV_KEY_MANAGER_HPP_

#include <boost/filesystem.hpp>

namespace trihlav {

/**
 * Manage key operations, fe. their persistence.
 */
class KeyManager {
public:
	typedef boost::filesystem::path path;

    /// Lazy initialization constructor.
    KeyManager(const path& pDir);

    KeyManager();

    virtual ~KeyManager();

    virtual const path& getConfigDir() const;

    void setConfigDir( const path& pPath );

    /**
     * Are all internal resources ready.
     */
    const bool isInitialized() const {
        return itsInitializedFlag;
    }

    /// Get users home directory
    static const path getHome();
private:
    mutable bool itsInitializedFlag;
    boost::filesystem::path itsConfigDir;
    const path detectConfigDir() const;
    void checkPath(const path& pPath, bool &readable, bool &writable) const;
};

} /* namespace trihlav */

#endif /* TRIHLAV_KEY_MANAGER_HPP_ */
