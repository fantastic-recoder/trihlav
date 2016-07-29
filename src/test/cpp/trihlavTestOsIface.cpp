/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 der GNU General Public License, wie von der Free Software Foundation,
 Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 veröffentlichten Version, weiterverbreiten und/oder modifizieren.

 Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.

 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */
#include <string>
#include <yubikey.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include <boost/filesystem.hpp>

#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavLib/trihlavOsIface.hpp"
#include "trihlavLib/trihlavLog.hpp"


using ::testing::Return;
using ::testing::NiceMock;
using ::trihlav::initLog;
using ::trihlav::OsIface;

class TestOsIface: public ::testing::Test {
public:
	virtual void SetUp() {
		BOOST_LOG_NAMED_SCOPE("TestOsIface::SetUp");
	}

	// Tears down the test fixture.
	virtual void TearDown() {
		BOOST_LOG_NAMED_SCOPE("TestOsIface::TearDown");
	}
};

TEST_F(TestOsIface,validateUser) {
	BOOST_LOG_NAMED_SCOPE("TestOsIface::validateUser");
	OsIface myOsIface;
	EXPECT_EQ(myOsIface.checkOsPswd("trihlav_tst_usr0","trihlav_tst_pswd0"),true)<<
			"To be able to pass this test ensure, that running system has an test "
			"user \"trihlav_tst_usr0\" with password \"trihlav_tst_pswd0\".";
//	const string myTstHex0("abcdef0123456789");
//	BOOST_LOG_TRIVIAL(debug)<< myTstHex0;
//	const string myTstMod0 { YubikoOtpKeyConfig::hex2Modhex(myTstHex0) };
//	BOOST_LOG_TRIVIAL(debug)<< myTstMod0;
//	EXPECT_NE(myTstMod0,myTstHex0)
//			<< "Hex encoded and decoded strings should not be equal.";
//	const string myTstRes0 { YubikoOtpKeyConfig::modhex2Hex(myTstMod0) };
//	BOOST_LOG_TRIVIAL(debug)<< myTstRes0;
//	EXPECT_EQ(myTstHex0,myTstRes0)
//			<< "Hex encoded and re-decoded strings should be equal.";
}


int main(int argc, char **argv) {
	initLog();
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}
