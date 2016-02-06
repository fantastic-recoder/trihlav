#include <yubikey.h>
#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/filesystem.hpp>

#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavLib/trihlavLog.hpp"

#include "trihlavGlobalFixture.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavUTimestamp.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavIEdit.hpp"
#include "trihlavLib/trihlavIYubikoOtpKeyView.hpp"

using namespace std;
using namespace trihlav;
using namespace boost;
using namespace boost::filesystem;

namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace src = boost::log::sources;

inline void logDebug_token(const yubikey_token_st& pToken) {
	BOOST_LOG_NAMED_SCOPE("logDebug_token");
	string myUid(YUBIKEY_UID_SIZE * 2 + 1, ' ');
	yubikey_hex_encode(&myUid[0], reinterpret_cast<const char*>(&pToken.uid),
	YUBIKEY_UID_SIZE);
	BOOST_LOG_TRIVIAL(debug)<< "yubikey_token_st:{";
	BOOST_LOG_TRIVIAL(debug)<< "   uid  :\""<< myUid.c_str() << "\"";
	BOOST_LOG_TRIVIAL(debug)<< "   ctr  :\""<< int(pToken.ctr) << "\"";
	BOOST_LOG_TRIVIAL(debug)<< "   use  :\""<< int(pToken.use) << "\"";
	BOOST_LOG_TRIVIAL(debug)<< "   rnd  :\""<< int(pToken.rnd) << "\"";
	BOOST_LOG_TRIVIAL(debug)<< "   tstpl:\""<< int(pToken.tstpl)<< "\"";
	BOOST_LOG_TRIVIAL(debug)<< "   tstph:\""<< int(pToken.tstph)<< "\"";
	BOOST_LOG_TRIVIAL(debug)<< "   crc  :\""<< int(pToken.crc) << "\"";
	BOOST_LOG_TRIVIAL(debug)<< "}";
}

/**
 * Test the yubico-c library text to string calls.
 */
TEST( trihlavApi, testHexToString ) {
	BOOST_LOG_NAMED_SCOPE("testHexToString");
	const char* K_TEST0 = "quantum";
	const size_t K_TEST0_SIZE = strlen(K_TEST0);
	string myTest0HexEncoded(K_TEST0_SIZE * 2 + 1, ' ');
	const string K_EXPECTED("7175616e74756d\0", K_TEST0_SIZE * 2 + 1);
	yubikey_hex_encode(&myTest0HexEncoded[0], K_TEST0, K_TEST0_SIZE);
	BOOST_LOG_TRIVIAL(debug)<< "Encoded \""<<K_TEST0<<"\" is \""
	<<myTest0HexEncoded.c_str() <<"\"";
	EXPECT_TRUE(myTest0HexEncoded == K_EXPECTED);
	BOOST_LOG_TRIVIAL(debug)<< "testHexToString() ok";
}

/**
 * Generate two OTPs, parse them and check token parts
 * @return void
 */
TEST( trihlavApi, testGenerateAndParse) {
	BOOST_LOG_NAMED_SCOPE("testGenerateAndParse");
	/* Decrypt TOKEN using KEY and store output in OUT structure.  Note
	 that there is no error checking whether the output data is valid or
	 not, use yubikey_check_* for that. */
	const uint8_t myKey[YUBIKEY_KEY_SIZE] = { 0xaa, 0xff, 0x0c, 0x00, 0xa1,
			0xef, 0x1c, 0x10, 0xa2, 0xdf, 0x3c, 0x30, 0xa3, 0xff, 0xcc, 0x60 };
	const char K_Y_UID[YUBIKEY_UID_SIZE + 1] = "012543";
	/* Generate OTP */
	yubikey_token_st myToken, myTokenBack;
	const size_t K_YBK_TKEN_SZ = sizeof(myToken);
	BOOST_LOG_TRIVIAL(debug)<< "sizeof(time_t)==%d",int(sizeof(time_t));
	UTimestamp myTstp;
	myTstp.tstp_int = time(0);
	memcpy(&myToken.uid, K_Y_UID, YUBIKEY_UID_SIZE);
	myToken.ctr = 3;
	myToken.use = 4;
	myToken.rnd = 42;
	myToken.tstpl = myTstp.tstp.tstpl;
	myToken.tstph = myTstp.tstp.tstph;
	myToken.crc = 0;
	myToken.crc = ~yubikey_crc16(reinterpret_cast<uint8_t*>(&myToken),
			K_YBK_TKEN_SZ - sizeof(myToken.crc));
	memcpy(&myTokenBack, &myToken, sizeof(myToken));
	logDebug_token(myTokenBack);
	char myOtp0[YUBIKEY_OTP_SIZE + 1], myOtp1[YUBIKEY_OTP_SIZE + 1];
	yubikey_generate(&myToken, myKey, myOtp0);
	BOOST_LOG_TRIVIAL(debug)<< "Generated yubikey OTP (0) " << myOtp0;
	yubikey_parse(reinterpret_cast<uint8_t*>(myOtp0), myKey, &myToken);
	logDebug_token(myToken);
	EXPECT_TRUE(myTokenBack.ctr == myToken.ctr);
	EXPECT_TRUE(myTokenBack.rnd == myToken.rnd);
	EXPECT_TRUE(myTokenBack.use == myToken.use);
	EXPECT_TRUE(myTokenBack.tstph == myToken.tstph);
	EXPECT_TRUE(myTokenBack.tstpl == myToken.tstpl);
	EXPECT_TRUE(
			strncmp( reinterpret_cast<const char*>(&myTokenBack.uid),
					reinterpret_cast<char*>(&myToken.uid), YUBIKEY_UID_SIZE)==0)
			<< "The uid-s are different!";
	uint16_t myCrc = yubikey_crc16(reinterpret_cast<uint8_t*>(&myToken),
	YUBIKEY_KEY_SIZE);
	BOOST_LOG_TRIVIAL(debug)<< "crc1="<<myCrc <<" - "<<YUBIKEY_CRC_OK_RESIDUE;
	EXPECT_TRUE(yubikey_crc_ok_p(reinterpret_cast<uint8_t*>(&myToken)))
			<< "CRC failed!";
	yubikey_generate(&myToken, myKey, myOtp1);
	BOOST_LOG_TRIVIAL(debug)<< "Generated yubikey OTP (1) "<<myOtp1;
	EXPECT_TRUE(strncmp(myOtp0, myOtp1, YUBIKEY_OTP_SIZE) == 0)
			<<"The (re)generatet keys are different!";
	BOOST_LOG_TRIVIAL(debug)<< "testGenerateAndParse() ok";
}

TEST( trihlavApi, testUTimestampMemLayout) {
	BOOST_LOG_NAMED_SCOPE("testUTimestampMemLayout");
	UTimestamp myTstp;
	myTstp.tstp_int = 0x6789ABCD;
	EXPECT_TRUE(sizeof(myTstp) == 4)
			<<"Memory alignment is not bytewise!";
	EXPECT_TRUE(int(myTstp.tstp.tstpl) == int(0x6789));
	EXPECT_TRUE(int(myTstp.tstp.tstph) == int(0xAB));
	EXPECT_TRUE(int(myTstp.tstp.filler) == int(0xCD));
}

TEST( trihlavApi, testLoadAndSaveKeyCfg) {
	BOOST_LOG_NAMED_SCOPE("testLoadAndSaveKeyCfg");
	path myTestCfgFile(unique_path("%%%%-%%%%-%%%%-%%%%.json"));
	BOOST_LOG_TRIVIAL(debug)<< "Test data location: '" << myTestCfgFile <<"'.";
	YubikoOtpKeyConfig myTestCfg0(myTestCfgFile);
	myTestCfg0.setPrivateId("010203040506");
	myTestCfg0.setTimestamp(UTimestamp(12345));
	myTestCfg0.setCounter(33);
	myTestCfg0.setRandom(44);
	myTestCfg0.setCrc(55);
	myTestCfg0.setUseCounter(7);
	EXPECT_TRUE(int(myTestCfg0.getToken().uid[0]) == 1);
	EXPECT_TRUE(int(myTestCfg0.getToken().uid[1]) == 2);
	EXPECT_TRUE(int(myTestCfg0.getToken().uid[2]) == 3);
	EXPECT_TRUE(int(myTestCfg0.getToken().uid[3]) == 4);
	EXPECT_TRUE(int(myTestCfg0.getToken().uid[4]) == 5);
	EXPECT_TRUE(int(myTestCfg0.getToken().uid[5]) == 6);
	BOOST_LOG_TRIVIAL(debug)<< "Private id:'" << myTestCfg0.getPrivateId() << "'.";
	EXPECT_TRUE(myTestCfg0.getPrivateId().compare("010203040506") == 0);

	EXPECT_TRUE(int(myTestCfg0.getToken().ctr) == 33);
	EXPECT_TRUE(int(myTestCfg0.getToken().rnd) == 44);
	EXPECT_TRUE(int(myTestCfg0.getToken().crc) == 55);
	EXPECT_TRUE(int(myTestCfg0.getToken().use) == 7);

	myTestCfg0.save();
	YubikoOtpKeyConfig myTestCfg1(myTestCfgFile);
	myTestCfg1.load();
	EXPECT_TRUE(myTestCfg0.getPrivateId() == myTestCfg1.getPrivateId());
	EXPECT_TRUE(
			myTestCfg0.getTimestamp().tstp_int
					== myTestCfg1.getTimestamp().tstp_int);
	EXPECT_TRUE(myTestCfg0.getCounter() == myTestCfg1.getCounter());
	EXPECT_TRUE(myTestCfg0.getCrc() == myTestCfg1.getCrc());
	EXPECT_TRUE(myTestCfg0.getRandom() == myTestCfg1.getRandom());
	EXPECT_TRUE(myTestCfg0.getUseCounter() == myTestCfg1.getUseCounter());

	remove(myTestCfgFile);
	BOOST_LOG_TRIVIAL(debug)<< "test file removed, testLoadAndSaveKeyCfg ok";
}

int main(int argc, char **argv) {
	initLog();
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}

