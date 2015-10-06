#ifndef YUSERCONFIG_HPP
#define YUSERCONFIG_HPP

#include <yubikey.h>
#include <string>

#include "trihlavUTimestamp.hpp"

namespace trihlavApi {

/**
 * @brief Store, load and provide the APIs configuration.
 */
class YubikoOtpKeyConfig
{
private:
    bool             itsChangedFlag;
    std::string      itsFilename;
    yubikey_token_st itsToken;
    uint8_t          itsKey[YUBIKEY_KEY_SIZE];

	const std::string checkFileName(bool pIsOut);

protected:
    void setFilename(const std::string &value);
public:
    /**
     * @brief YubikoOtpKeyConfig::YubikoOtpKeyConfig
     */
    YubikoOtpKeyConfig(const std::string& pDataPathDir);

    /**
     * @brief getPrivateId access the private id config value
     */
    const std::string getPrivateId() const;

    /**
     * @brief Timestamp incremented by approx 8Hz.
     * @see UTimestamp
     * @return yubikey_token_st.tstpl and yubikey_token_st.tstph
     */
    const UTimestamp getTimestamp() const  {
        UTimestamp myRetVal;
        myRetVal.tstp.tstpl = itsToken.tstpl;
        myRetVal.tstp.tstph = itsToken.tstph;
        return myRetVal;
    }

    /**
     * @brief setter, see getTimestamp()
     * @param pVal new value of timestamp values.
     */
    void setTimestamp( const UTimestamp pVal ) {
        itsToken.tstpl = pVal.tstp.tstpl ;
        itsToken.tstph = pVal.tstp.tstph;
    }

    /**
     * @brief setPrivateId sets the private id part of the Yubikey token
     */
    void setPrivateId(const std::string& pPrivateId);

    /**
     * @brief The random value of Yubiko token.
     * @return the random filler as integer.
     */
    uint16_t getRandom() const {
        return getToken().rnd;
    }

    /**
     * @brief @see getRandom()
     * @param pRandom new random value of the Yubiko token.
     */
    void setRandom( const uint16_t pRandom ) {
        getToken().rnd=pRandom;
    }

    /**
     * @brief Number of times used within session + activation flags.
     * @return The use counter in the Yubiko token.
     */
    uint8_t getCounter() const {
        return getToken().ctr;
    }

    /**
     * @brief @see getCounter()
     * @param pCounter The new value for the use counter.
     */
    void setCounter( const uint16_t pCounter ) {
        getToken().ctr=pCounter;
    }

    /**
     * @brief Number of times used within session + activation flags.
     * @return The use counter in the Yubiko token.
     */
    uint8_t getUseCounter() const {
        return getToken().use;
    }

    /**
     * @brief @see getUse()
     * @param pUse The new value for the use counter.
     */
    void setUseCounter( const uint8_t pUse ) {
        getToken().use=pUse;
    }

    /**
     * @brief CRC16 value of all fields.
     * @return The CRC16 value in the Yubiko token.
     */
    uint16_t getCrc() const {
        return getToken().crc;
    }

    /**
     * @brief @see getCrc()
     * @param pCrc The new value for the CRC16 value.
     */
    void setCrc( const uint16_t pCrc ) {
        getToken().crc=pCrc;
    }

    /**
     * @brief save the configuration values to passed filename.
     */
    void save();

    /**
     * @brief load the configuration values from passed filename.
     */
    void load();

    /**
     * @brief ~YubikoOtpKeyConfig
     */
    virtual ~YubikoOtpKeyConfig();

    /**
     * @brief Getter.
     * @return The filename of the of the keys config file.
     */
    const std::string& getFilename() const
    {
        return itsFilename;
    }

    /**
     * @return The Yubikey constant token.
     */
    const yubikey_token_st& getToken() const {
    	return itsToken;
    }

    /**
     * @return The Yubikey token.
     */
    yubikey_token_st& getToken() {
        return itsToken;
    }

};

} // end namespace


#endif // YUSERCONFIG_HPP
