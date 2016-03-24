#include <string>
#include <iostream>
#include <exception>
#include <sstream>
#include <vector>
#include <array>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/format.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "pretty.hpp"
#include "yubikey.h"

#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavWrongConfigValue.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavEmptyPublicId.hpp"
#include "trihlavLib/trihlavLog.hpp"

using std::cout;
using std::ostringstream;
using std::string;
using std::out_of_range;
using std::vector;
using std::array;
using std::stringstream;

using boost::trim;
using boost::format;
using boost::property_tree::ptree;
using boost::filesystem::path;
using boost::filesystem::unique_path;
using boost::date_time::date;
using boost::date_time::day_clock;
using namespace boost::posix_time;

#include "pretty.hpp"
#include "trihlavEmptyPublicId.hpp"

typedef array<uint8_t, YUBIKEY_UID_SIZE + 1> OTP_t;

PRETTY_DEFAULT_DECORATION(vector<int>, "[[", "||", ">")

namespace {
static constexpr uintmax_t K_MX_KEY_FILE_SZ = 1024;
static constexpr uintmax_t K_SEC_KEY_SZ = YUBIKEY_KEY_SIZE * 2;
}

namespace trihlav {

static constexpr size_t K_YBK_PRIVATE_ID_LEN(YUBIKEY_UID_SIZE * 2);
static const string K_NM_DOC_NM("yubikey.");
static const string K_NM_PRIV_ID("privateId");
static const string K_NM_PUB_ID("publicId");
static const string K_NM_TIMESTAMP("timestamp");
static const string K_NM_SES_CNTR("counter");
static const string K_NM_USE_CNTR("use");
static const string K_NM_SEC_KEY("secretKey");
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
YubikoOtpKeyConfig::YubikoOtpKeyConfig(KeyManager& pKeyManager,
		const bfs::path& pFilename) :
		itsKeyManager(pKeyManager), itsChangedFlag(false), itsFilename(
				pFilename) {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::YubikoOtpKeyConfig");
	BOOST_LOG_TRIVIAL(debug)<< "Passed filename:  " << pFilename.native();
	zeroToken();
}

/**
 *
 */
YubikoOtpKeyConfig::YubikoOtpKeyConfig(KeyManager& pKeyManager) :
		itsKeyManager(pKeyManager), itsChangedFlag(false) {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::YubikoOtpKeyConfig");
	path myFilename = itsKeyManager.getConfigDir()
			/ "%%-%%-%%.trihlav-key.json";
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
	string myRetVal(K_YBK_PRIVATE_ID_LEN, '.');
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
	string myRetVal(K_SEC_KEY_SZ, '.');
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
		yubikey_hex_decode(reinterpret_cast<char*>(itsKey.data()),
				mySecretKey.c_str(),
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
			ptime myTime= microsec_clock::universal_time();
			stringstream myStrStr;
			myStrStr << "." << myTime;
			path myBackup(getFilename());
			myBackup+=(myStrStr.str());
			BOOST_LOG_TRIVIAL(debug)<< "Moving "<< getFilename() << " to "<<myBackup;
			rename(getFilename(), myBackup);
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
	setPublicId(myTree.get<string>(K_NM_DOC_NM + K_NM_PUB_ID));
	setSecretKey(myTree.get<string>(K_NM_DOC_NM + K_NM_SEC_KEY));
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
	myTree.put(K_NM_DOC_NM + K_NM_PUB_ID /*---->*/, getPublicId());
	myTree.put(K_NM_DOC_NM + K_NM_SEC_KEY /*--->*/, getSecretKey());
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

/**
 * The description will not be compared, only the token, public ID and secret
 * key are being considered.
 *
 * @return true when core settings are same.
 */
bool YubikoOtpKeyConfig::operator ==(const YubikoOtpKeyConfig& pOther) const {
	if (memcmp(&this->getToken(), &pOther.getToken(), sizeof(yubikey_token_st))
			!= 0) {
		BOOST_LOG_TRIVIAL(debug)<< "Token "
		<< this->token2json() << "!=" << pOther.token2json();
		return false;
	}
	if (this->getPublicId().compare(pOther.getPublicId()) !=0 ) {
		BOOST_LOG_TRIVIAL(debug)<< "PublicId "
		<< this->getPublicId() << "!=" << pOther.getPublicId();
		return false;
	}
	if (memcmp(&this->itsKey, &pOther.itsKey,sizeof(itsKey)) !=0 ) {
		BOOST_LOG_TRIVIAL(debug)<< "Secret key "
		<< this->getSecretKey() << "!=" << pOther.getSecretKey();
		return false;
	}
	return true;
}

YubikoOtpKeyConfig::~YubikoOtpKeyConfig() {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::~YubikoOtpKeyConfig");
}

void YubikoOtpKeyConfig::setFilename(const string &value) {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::setFilename");
	itsFilename = value;
}

const string YubikoOtpKeyConfig::token2json() const {
	string myUid(YUBIKEY_UID_SIZE * 2 + 1, ' ');
	yubikey_hex_encode(&myUid[0],
			reinterpret_cast<const char*>(&getToken().uid),
			YUBIKEY_UID_SIZE);
	ostringstream myOstr;
	myOstr << "yubikey_token_st:{";
	myOstr << "   uid  :\"" << myUid.c_str() << "\"";
	myOstr << "   ctr  :\"" << int(getToken().ctr) << "\"";
	myOstr << "   use  :\"" << int(getToken().use) << "\"";
	myOstr << "   rnd  :\"" << int(getToken().rnd) << "\"";
	myOstr << "   tstpl:\"" << int(getToken().tstpl) << "\"";
	myOstr << "   tstph:\"" << int(getToken().tstph) << "\"";
	myOstr << "   crc  :\"" << int(getToken().crc) << "\"";
	myOstr << "}";
	return myOstr.str();
}

/**
 * @return The public ID encoded in Modhex mode.
 */
const string YubikoOtpKeyConfig::getPublicIdModhex() const {
	return hex2Modhex(getPublicId());
}

/**
 * The Modhex encoding is described in Yubikey manual, as a start point You
 * can read this: @link https://www.yubico.com/modhex-calculator/ .
 * @param p2Modhex what to encode.
 * @return input Modhex encoded.
 *
 */
const string YubikoOtpKeyConfig::hex2Modhex(const string& p2Modhex) {
	const unsigned long mySz = p2Modhex.size();
	const unsigned long mySz2 = mySz / 2;
	vector<uint8_t> myBytes(mySz2, uint8_t(0));
	yubikey_hex_decode(reinterpret_cast<char*>(&myBytes[0]), p2Modhex.c_str(),
			mySz);
	string myPubId(mySz + 1, '\0');
	yubikey_modhex_encode(&myPubId[0], reinterpret_cast<char*>(&myBytes[0]),
			mySz2);
	myPubId.resize(mySz);
	return myPubId;
}

/**
 * @see const string hex2Modhex(const string& p2Modhex) const;
 * @param p2Hex what to decode.
 * @return input from Modhex decoded.
 *
 */
const string YubikoOtpKeyConfig::modhex2Hex(const std::string& p2Hex) {
	const unsigned long mySz = p2Hex.size();
	const unsigned long mySz2 = mySz / 2;
	vector<uint8_t> myBytes(mySz2, uint8_t(0));
	yubikey_modhex_decode(reinterpret_cast<char*>(&myBytes[0]), p2Hex.c_str(),
			mySz2);
	string myPubId(mySz + 1, '\0');
	yubikey_hex_encode(&myPubId[0], reinterpret_cast<char*>(&myBytes[0]),
			mySz2);
	myPubId.resize(mySz);
	return myPubId;
}

void YubikoOtpKeyConfig::setPublicId(const std::string& pPubId) {
	auto myOldKey = itsPublicId;
	if (pPubId.empty()) {
		throw new EmptyPublicId();
	}
	itsPublicId = pPubId;
	itsKeyManager.update(pPubId, *this);
}

/**
 * @param pPswd2check modhex encoded
 */
bool YubikoOtpKeyConfig::checkOtp(const std::string& pPswd2check) {
	BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyConfig::checkPassword");
	yubikey_token_st myToken;
	yubikey_parse(reinterpret_cast<const uint8_t*>(pPswd2check.c_str()),
			this->getSecretKeyArray().data(), &myToken);
	BOOST_LOG_TRIVIAL(debug)<< "Key token:";
	logDebug_token(getToken());
	BOOST_LOG_TRIVIAL(debug)<< "Decrypted token:";
	logDebug_token(myToken);
	//	EXPECT_TRUE(myTokenBack.ctr == myToken.ctr);
	//	EXPECT_TRUE(myTokenBack.rnd == myToken.rnd);
	//	EXPECT_TRUE(myTokenBack.use == myToken.use);
	//	EXPECT_TRUE(myTokenBack.tstph == myToken.tstph);
	//	EXPECT_TRUE(myTokenBack.tstpl == myToken.tstpl);
	if (strncmp(reinterpret_cast<const char*>(&getToken().uid),
			reinterpret_cast<char*>(&myToken.uid), YUBIKEY_UID_SIZE) == 0) {
		BOOST_LOG_TRIVIAL(debug)<< "UID is same.";
		uint16_t myComputedCrc = computeCrc(myToken);
		if(myToken.crc!=myComputedCrc) {
			BOOST_LOG_TRIVIAL(debug)<< "Decrypted CRC is wrong: "
			<< myComputedCrc <<"!=" << myToken.crc;
			return false;
		}
		if(myToken.use <= getToken().use) {
			BOOST_LOG_TRIVIAL(debug)<< "Decrypted use counter is wrong: "
			<< myToken.use <<"<=" << getToken().use;
			return false;
		}
		if(myToken.ctr != getToken().ctr) {
			BOOST_LOG_TRIVIAL(debug)<< "Decrypted counter is wrong: "
			<< myToken.ctr <<"!=" << getToken().ctr;
			return false;
		}
		setCounter(myToken.ctr);
		setUseCounter(myToken.use);
		getToken().tstph=myToken.tstph;
		getToken().tstpl=myToken.tstpl;
		computeCrc();
		save();
		BOOST_LOG_TRIVIAL(debug)<< "OTP OK!";
		return true;
	}
	return false;
}

uint16_t YubikoOtpKeyConfig::computeCrc(const yubikey_token_st& pToken) {
	return ~yubikey_crc16(reinterpret_cast<const uint8_t*>(&pToken),
			sizeof(pToken) - sizeof(pToken.crc));
}

} // end namespace trihlav
