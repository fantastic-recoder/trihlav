/*
 * trihlavKeyManager.hpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_KEY_MANAGER_HPP_
#define TRIHLAV_KEY_MANAGER_HPP_

#include <map>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

namespace trihlav {

class YubikoOtpKeyConfig;

/**
 * Manage key operations, fe. their persistence.
 */
class KeyManager {
public:
	using path = boost::filesystem::path;
	using KeyList_t = std::vector<std::shared_ptr<YubikoOtpKeyConfig> >;
	using KeyMap_t = std::map<std::string,YubikoOtpKeyConfig*>;

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

    /// @brief Load or reload all keys.
    size_t loadKeys();

    /// @brief How many keys are currently loaded?
    const size_t getKeyCount() const;

    /// @brief Access an loaded key.
    const YubikoOtpKeyConfig& getKey( const size_t pIdx) const;

    /// @brief Access an loaded key.
    const YubikoOtpKeyConfig* getKeyByPublicId( const std::string& pPubId) const;

    /// @brief Access an loaded key.
    YubikoOtpKeyConfig* getKeyByPublicId( const std::string& pPubId);

    /// @brief Get users home directory
    static const path getHome();

	void update(const std::string& pPubId,YubikoOtpKeyConfig& pKey);

private:
	void renameMallformedKeyFile(const path& pKyFileFName);
    mutable bool itsInitializedFlag;
    boost::filesystem::path itsConfigDir;
    KeyList_t itsKeyList;
    KeyMap_t  itsKeyMapByPublicId;
    const path detectConfigDir() const;
    void checkPath(const path& pPath, bool &readable, bool &writable) const;
};

} /* namespace trihlav */

#endif /* TRIHLAV_KEY_MANAGER_HPP_ */
