#include <string>
#include <iostream>
#include <exception>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/format.hpp>

#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "yubikey.h"
#include "trihlavLib/trihlavWrongConfigValue.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"

using std::cout;
using std::string;
using std::out_of_range;
using boost::trim;
using boost::format;
using boost::property_tree::ptree;
using boost::filesystem::path;
using boost::filesystem::unique_path;

namespace {
static const uintmax_t K_MX_KEY_FILE_SZ = 1024;
static const uintmax_t K_SEC_KEY_SZ = YUBIKEY_KEY_SIZE * 2;
}

namespace trihlav {

static const size_t K_YBK_PRIVATE_ID_LEN(YUBIKEY_UID_SIZE * 2);
static const string K_NM_DOC_NM("yubikey.");
static const string K_NM_PRIV_ID("privateId");
static const string K_NM_TIMESTAMP("timestamp");
static const string K_NM_SES_CNTR("counter");
static const string K_NM_USE_CNTR("use");
static const string K_NM_RANDOM("random");
static const string K_NM_CRC("crc");
static const string K_NM_DESC("description");
static const string K_NM_VERS("version");
static const string K_VL_VERS("0.0.1");

void YubikoOtpKeyConfig::zeroToken() {
	memset(&itsToken, 0, sizeof(yubikey_token_st));
	memset(&itsKey, 0, YUBIKEY_KEY_SIZE);
}

/**
 * Just initialize fields, does not loads the data.
 *
 * @param pFilename Where the configuration data will be stored.
 */
YubikoOtpKeyConfig::YubikoOtpKeyConfig(KeyManager& pKeyManager, const bfs::path& pFilename)
: itsKeyManager(pKeyManager)
, itsChangedFlag(false)
, itsFilename(pFilename)
{
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::YubikoOtpKeyConfig");
	BOOST_LOG_TRIVIAL(debug) << "Passed filename:  " << pFilename.native();
	zeroToken();
}

/**
 *
 */
YubikoOtpKeyConfig::YubikoOtpKeyConfig(KeyManager& pKeyManager)
: itsKeyManager(pKeyManager)
, itsChangedFlag(false)
{
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::YubikoOtpKeyConfig");
	path myFilename = itsKeyManager.getConfigDir() / "%%-%%-%%";
	itsFilename = unique_path(myFilename);
	zeroToken();
}
/**
 * Getter.
 *
 * @return Hex-encoded string representing the private id Yubikey token part.
 */
const string YubikoOtpKeyConfig::getPrivateId() const {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::getPrivateId");
	string myRetVal(K_YBK_PRIVATE_ID_LEN, '\0');
	yubikey_hex_encode(&myRetVal[0],
			reinterpret_cast<const char*>(&itsToken.uid), YUBIKEY_UID_SIZE);
	return string(myRetVal);
}

/**
 * Setter.
 *
 * @param pPrivateId Hex-encoded string representing the private id Yubikey token part.
 */
void YubikoOtpKeyConfig::setPrivateId(const string &pPrivateId) {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::setPrivateId");
	string myPrivateId(pPrivateId);
	trim(myPrivateId);
	if (myPrivateId.size() != K_YBK_PRIVATE_ID_LEN) {
		throw new WrongConfigValue(WrongConfigValue::EYbkPrivateId,
				K_YBK_PRIVATE_ID_LEN, myPrivateId.size());
	}
	if (getPrivateId() != pPrivateId) {
		yubikey_hex_decode(reinterpret_cast<char*>(itsToken.uid),
				myPrivateId.c_str(), YUBIKEY_UID_SIZE);
		itsChangedFlag = true;
	}
}

const std::string YubikoOtpKeyConfig::getSecretKey() const {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::getSecretKey()");
	string myRetVal(K_SEC_KEY_SZ, '\0');
	yubikey_hex_encode(&myRetVal[0], reinterpret_cast<const char*>(&itsKey),
	YUBIKEY_KEY_SIZE);
	return string(myRetVal);
}

void YubikoOtpKeyConfig::setSecretKey(const std::string& pKey) {
	BOOST_LOG_NAMED_SCOPE(
			"YubikoOtpKeyConfig::setSecretKey( const std::string& pKey)");
	string mySecretKey(pKey);
	trim(mySecretKey);
	if (mySecretKey.size() != K_SEC_KEY_SZ) {
		throw new WrongConfigValue(WrongConfigValue::EYbkSecretKey,
				K_SEC_KEY_SZ, mySecretKey.size());
	}
	if (getSecretKey() != pKey) {
		yubikey_hex_decode(reinterpret_cast<char*>(itsKey), mySecretKey.c_str(),
		YUBIKEY_KEY_SIZE);
		itsChangedFlag = true;
	}
}

const string YubikoOtpKeyConfig::checkFileName(bool pIsOut) {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::checkFileName");
	std::string myRetVal;
	if (is_directory(getFilename())) {
		const string myMsg =
				(format("File %1% is a directory.") % getFilename()).str();
		BOOST_LOG_TRIVIAL(error)<< myMsg;
		throw new out_of_range(myMsg);
	}
	if (pIsOut) {
		if (exists(getFilename())) {
			const string myMsg = (format("File %1% already exists.")
					% getFilename()).str();
			BOOST_LOG_TRIVIAL(error)<< myMsg;
			throw new out_of_range(myMsg);
		}
		myRetVal = getFilename().native();
	} else {
		if (!exists(getFilename())) {
			const string myMsg = (format("Couldn't open save file %1%.")
					% getFilename()).str();
			BOOST_LOG_TRIVIAL(error)<< myMsg;
			throw new out_of_range(myMsg);
		}
		uintmax_t myFSz = file_size(getFilename());
		if (myFSz > K_MX_KEY_FILE_SZ) {
			const string myMsg = (format("File %1% is too big: %2%.")
					% getFilename() % myFSz).str();
			BOOST_LOG_TRIVIAL(error)<< myMsg;
			throw new out_of_range(myMsg);
		}
		myRetVal = getFilename().native();
	}
	return myRetVal;
}

void YubikoOtpKeyConfig::load() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::load");
	const string myInFile = checkFileName(false);
	ptree myTree;
	read_json(myInFile, myTree);
	const string myVer(myTree.get<string>(K_NM_DOC_NM + K_NM_VERS));
	BOOST_LOG_TRIVIAL(info)<< K_NM_VERS << ":" << myVer;
	setPrivateId(myTree.get<string>(K_NM_DOC_NM + K_NM_PRIV_ID));
	setTimestamp(
			UTimestamp(myTree.get<uint64_t>(K_NM_DOC_NM + K_NM_TIMESTAMP)));
	setCounter(myTree.get<uint8_t>(K_NM_DOC_NM + K_NM_SES_CNTR));
	setCrc(myTree.get<uint16_t>(K_NM_DOC_NM + K_NM_CRC));
	setRandom(myTree.get<uint16_t>(K_NM_DOC_NM + K_NM_RANDOM));
	setUseCounter(myTree.get<uint8_t>(K_NM_DOC_NM + K_NM_USE_CNTR));
	setDescription(myTree.get<string>(K_NM_DOC_NM + K_NM_DESC));
	itsChangedFlag = false;
}

/**
 * Save the key data in a JSON like format. The filename is specified in
 * constructor YubikoOtpKeyConfig::YubikoOtpKeyConfig(const string& )
 */
void YubikoOtpKeyConfig::save() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::save");
	const string myOutFile = checkFileName(true);
	ptree myTree;
	myTree.put(K_NM_DOC_NM + K_NM_PRIV_ID /*--->*/, getPrivateId());
	myTree.put(K_NM_DOC_NM + K_NM_TIMESTAMP /*->*/, getTimestamp().tstp_int);
	myTree.put(K_NM_DOC_NM + K_NM_SES_CNTR /*-->*/, getCounter());
	myTree.put(K_NM_DOC_NM + K_NM_CRC /*------->*/, getCrc());
	myTree.put(K_NM_DOC_NM + K_NM_RANDOM /*---->*/, getRandom());
	myTree.put(K_NM_DOC_NM + K_NM_USE_CNTR /*-->*/, getUseCounter());
	myTree.put(K_NM_DOC_NM + K_NM_DESC /*------>*/, getDescription());
	myTree.put(K_NM_DOC_NM + K_NM_VERS /*------>*/, K_VL_VERS);
	write_json(myOutFile, myTree);
	itsChangedFlag = false;
}

YubikoOtpKeyConfig::~YubikoOtpKeyConfig() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::~YubikoOtpKeyConfig");
}

void YubikoOtpKeyConfig::setFilename(const string &value) {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::setFilename");
	itsFilename = value;
}

} // end namespace yuSerApi

