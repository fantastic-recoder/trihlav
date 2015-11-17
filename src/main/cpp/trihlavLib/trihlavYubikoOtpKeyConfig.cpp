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

#include "trihlavYubikoOtpKeyConfig.hpp"
#include "yubikey.h"
#include "trihlavWrongConfigValue.hpp"

using namespace std;
using namespace boost;
using namespace boost::filesystem;
using std::cout;
using boost::property_tree::ptree;

namespace {
static const uintmax_t K_MX_KEY_FILE_SZ = 1024;
}

namespace trihlavApi {

static const size_t K_YBK_PRIVATE_ID_LEN(YUBIKEY_UID_SIZE * 2);
static const string K_NM_DOC_NM("yubikey.");
static const string K_NM_PRIV_ID("privateId");
static const string K_NM_TIMESTAMP("timestamp");
static const string K_NM_SES_CNTR("counter");
static const string K_NM_USE_CNTR("use");
static const string K_NM_RANDOM("random");
static const string K_NM_CRC("crc");
static const string K_NM_KEY("key");

/**
 * ResDium's Yubikey Server API settings.
 */
//QSettings theYuSerApiSettings("ResDium","yuSerApi");
/**
 * Just init fields, does not loads the data.
 * @param pDataPathDir Where the config data will be stored.
 */
YubikoOtpKeyConfig::YubikoOtpKeyConfig(const bfs::path& pPath2KeyKonfig) :
		itsChangedFlag(false), itsFilename(pPath2KeyKonfig) {
	memset(&itsToken, 0, sizeof(yubikey_token_st));
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::YubikoOtpKeyConfig");
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

const string YubikoOtpKeyConfig::checkFileName(bool pIsOut) {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::checkFileName");
	std::string myRetVal;
	if (pIsOut) {
		if (exists(getFilename())) {
			throw new out_of_range(
					(format("File \"%1\" already exists.") % getFilename()).str());
		}
		myRetVal = getFilename().native();
	} else {
		if (!exists(getFilename())) {
			throw new out_of_range(
					(format("Couldn't open save file \"%1\".") % getFilename()).str());
		}
		uintmax_t myFSz = file_size(getFilename());
		if (myFSz > K_MX_KEY_FILE_SZ) {
			throw new out_of_range(
					(format("File \"%\" is too big: %.") % getFilename() % myFSz).str());
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
	setPrivateId(myTree.get<string>(K_NM_DOC_NM + K_NM_PRIV_ID));
	setTimestamp(
			UTimestamp(myTree.get<uint64_t>(K_NM_DOC_NM + K_NM_TIMESTAMP)));
	setCounter(myTree.get<uint8_t>(K_NM_DOC_NM + K_NM_SES_CNTR));
	setCrc(myTree.get<uint16_t>(K_NM_DOC_NM + K_NM_CRC));
	setRandom(myTree.get<uint16_t>(K_NM_DOC_NM + K_NM_RANDOM));
	setUseCounter(myTree.get<uint8_t>(K_NM_DOC_NM + K_NM_USE_CNTR));

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
	write_json(myOutFile, myTree);
	itsChangedFlag = false;
}

YubikoOtpKeyConfig::~YubikoOtpKeyConfig() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::~YubikoOtpKeyConfig");
	if (itsChangedFlag) {
		save();
	}
}

void YubikoOtpKeyConfig::setFilename(const string &value) {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::setFilename");
	itsFilename = value;
}

} // end namespace yuSerApi

