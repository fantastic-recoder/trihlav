/*
 * trihlavKeyManager.cpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#include <string>
#include <ios>
#include <iostream>
#include <fstream>
#include <memory>
#include <list>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#if defined _WIN32 || defined _WIN64
#include <windows.h>
#include <stdio.h>
#include <lmcons.h>
#endif

#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavSettings.hpp"

using std::string;
using std::list;
using boost::filesystem::path;
using boost::filesystem::recursive_directory_iterator;
using boost::filesystem::perms;
using boost::regex_match;
using boost::format;

namespace trihlav {

    using YubikoOtpKeyConfigPtr= std::shared_ptr<YubikoOtpKeyConfig>;

/**
 *  @param pConfigDir The directory where to store the key configuration data.
 */
    KeyManager::KeyManager(const Settings &pSettings) //
            : m_Settings(pSettings) //
    {
        BOOST_LOG_NAMED_SCOPE("KeyManager::KeyManager");
    }

    KeyManager::~KeyManager() {
        BOOST_LOG_NAMED_SCOPE("KeyManager::~KeyManager");
    }


    void KeyManager::prefixKeyFile(const path &pKeyFileFName, const std::string &pPrefix) const {
        BOOST_LOG_NAMED_SCOPE("KeyManager::renameMallformedKeyFile");
        path myNewFName;
        try {
            if (exists(pKeyFileFName)) {
                path myPath = pKeyFileFName.parent_path();
                path myFName = pKeyFileFName.filename();
                myNewFName = myPath / (path(pPrefix + "-") += myFName);
                BOOST_LOG_TRIVIAL(debug) << "Going to rename " << pKeyFileFName << " into " << myNewFName << ".";
                rename(pKeyFileFName, myNewFName);
            } else {
                BOOST_LOG_TRIVIAL(debug) << "File " << pKeyFileFName << " does not exist.";
            }
        } catch (const std::exception &myExc) {
            BOOST_LOG_TRIVIAL(error) << "Failed to rename " << pKeyFileFName << " into " << myNewFName << "because - "
                                     << myExc.what();
        } catch (...) {
            BOOST_LOG_TRIVIAL(error) << "Failed to rename " << pKeyFileFName << " into " << myNewFName << ".";
        }
    }


    const boost::regex K_KEY_FILTER("[a-z0-9]{2,2}-[a-z0-9]{2,2}-[a-z0-9]{2,2}\\.trihlav-key\\.json");

/**
 * @return the loaded keys count.
 */
    size_t KeyManager::loadKeys() {
        BOOST_LOG_NAMED_SCOPE("KeyManager::loadKeys");
        m_KeyList.resize(0);
        m_KeyMapByPublicId.clear();
        list<path> myDamagedFiles;
        for (auto it = recursive_directory_iterator(getSettings().getConfigDir());
             it != recursive_directory_iterator(); it++) {
            boost::smatch matchProd;
            const path myFNameWithPath(it->path().native());
            const path myFName(it->path().filename().native());
            if (!is_directory(it->path())
                && regex_match(myFName.string(), matchProd, K_KEY_FILTER)) {
                BOOST_LOG_TRIVIAL(debug) << "Found key file " << myFName << ".";
                try {
                    YubikoOtpKeyConfig *myCfg = new YubikoOtpKeyConfig(*this, myFNameWithPath);
                    myCfg->load();
                    YubikoOtpKeyConfigPtr myKey{myCfg};
                    m_KeyList.emplace_back(myKey);
                    string myId(myKey->getPublicId());
                    if (myId.empty()) {
                        (myId += "generated:") += myKey->getFilename().string();
                    }
                    m_KeyMapByPublicId.emplace(KeyMap_t::value_type {myId, myKey.get()});
                } catch (std::exception &myExc) {
                    BOOST_LOG_TRIVIAL(error) << "Exception caugh while loading key file \"" << myFName << "\" - "
                                             << myExc.what();
                    myDamagedFiles.push_back(myFNameWithPath);
                } catch (...) {
                    BOOST_LOG_TRIVIAL(error) << "Unknown exception caugh while loading key file \"" << myFName << "\".";
                    myDamagedFiles.push_back(myFNameWithPath);
                }
            } else {
                BOOST_LOG_TRIVIAL(debug) << "Skipping file  " << myFName << ".";
            }
        }
        for (path myFName : myDamagedFiles) {
            prefixKeyFile(myFName, "damaged");
        }
        return m_KeyList.size();
    }

    const size_t KeyManager::getKeyCount() const {
        return m_KeyList.size();
    }

    const YubikoOtpKeyConfig &KeyManager::getKey(const size_t pIdx) const {
        if (pIdx < 0 || m_KeyList.size() < pIdx) {
            throw std::range_error(
                    (format("Key index %1% is out of range <0,%2%>.") % pIdx
                     % m_KeyList.size()).str());
        }
        return *(m_KeyList[pIdx]);
    }

/**
 * @param pPubId modhex encoded public id prefix.
 */
    const YubikoOtpKeyConfig *KeyManager::getKeyByPublicId(
            const string &pPubId) const {
        BOOST_LOG_NAMED_SCOPE("KeyManager::getKeyByPublicId const");
        auto myKey = m_KeyMapByPublicId.find(pPubId);
        if (myKey == m_KeyMapByPublicId.end()) {
            BOOST_LOG_TRIVIAL(warning) << "Key prefixed " << pPubId << " has not been found.";
            return 0;
        }
        return myKey->second;
    }

/**
 * @see getKeyByPublicId(const string& pPubId) const
 */
    YubikoOtpKeyConfig *KeyManager::getKeyByPublicId(const string &pPubId) {
        BOOST_LOG_NAMED_SCOPE("KeyManager::getKeyByPublicId");
        auto myKey = m_KeyMapByPublicId.find(pPubId);
        if (myKey == m_KeyMapByPublicId.end()) {
            BOOST_LOG_TRIVIAL(warning) << "Key prefixed " << pPubId << " has not been found.";
            return 0;
        }
        return myKey->second;
    }

    void KeyManager::update(const std::string &pPubId, YubikoOtpKeyConfig &pKey) {
        if (!pPubId.empty()) {
            const auto myIt = m_KeyMapByPublicId.find(pPubId);
            if (myIt != m_KeyMapByPublicId.end()) {
                if (myIt->second->getPrivateId().compare(pKey.getPrivateId())
                    == 0) {
                    m_KeyMapByPublicId.erase(myIt);
                }
            } else {
                BOOST_LOG_TRIVIAL(debug) << "Public id " << pPubId << " has not been found.";
            }
            m_KeyMapByPublicId[pKey.getPublicId()] = &pKey;
        } else {
            BOOST_LOG_TRIVIAL(debug) << "Public id is empty.";
        }
    }

    const Settings &KeyManager::getSettings() const {
        return m_Settings;
    }

}

/* namespace trihlav */
