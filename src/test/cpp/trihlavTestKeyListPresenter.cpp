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

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include <boost/filesystem.hpp>

#include "../../main/cpp/trihlavLib/trihlavButtonIface.hpp"
#include "../../main/cpp/trihlavLib/trihlavFactoryIface.hpp"
#include "../../main/cpp/trihlavLib/trihlavKeyListViewIface.hpp"
#include "../../main/cpp/trihlavLib/trihlavYubikoOtpKeyViewIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavLib/trihlavLog.hpp"
#include "trihlavLib/trihlavKeyListPresenter.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"

#include "trihlavMockButton.hpp"
#include "trihlavMockStrEdit.hpp"
#include "trihlavMockSpinBox.hpp"
#include "trihlavMockFactory.hpp"
#include "trihlavMockYubikoOtpKeyView.hpp"
#include "trihlavMockKeyListView.hpp"

#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavMockEditIface.hpp"

using namespace std;
using namespace trihlav;
using namespace boost;
using namespace boost::filesystem;

using ::testing::Return;
using ::testing::NiceMock;

class TestKeyListPresenter: public ::testing::Test {
public:
	virtual void SetUp() {
		BOOST_LOG_NAMED_SCOPE("TestKeyListPresenter::SetUp");
	}

	// Tears down the test fixture.
	virtual void TearDown() {
		BOOST_LOG_NAMED_SCOPE("TestKeyListPresenter::TearDown");
	}
};

TEST_F(TestKeyListPresenter,canAddYubikoKey) {
	BOOST_LOG_NAMED_SCOPE("TestKeyListPresenter::canAddYubikoKey");
	NiceMock<MockFactory> myMockFactory;

	KeyListPresenter myKeyListPresenter(myMockFactory);
	YubikoOtpKeyPresenter& myYubikoOtpKeyPresenter =
			myKeyListPresenter.getYubikoOtpKeyPresenter();
	YubikoOtpKeyViewIface& myView(myYubikoOtpKeyPresenter.getView());
	MockYubikoOtpKeyView& myMockYubikoOtpKeyView =
			dynamic_cast<MockYubikoOtpKeyView&>(myView);
	KeyListViewIface& myKeyListView = myKeyListPresenter.getView();
	EXPECT_CALL(myMockYubikoOtpKeyView, show());
	myKeyListView.getBtnAddKey().getPressedSignal()();
}

static const char* K_TST_DESC0 = "Test key 1";
static const char* K_TST_PRIV0="aabbaabbaabb";
static const char* K_TST_PUBL0="ccddccddccdd";
static const char* K_TST_SECU0="ddeeddeeddeeddeeddeeddeeddeeddee";
static const int K_TST_CNTR0 = 1;
static const int K_TST_RNDM0 = 11;
static const char* K_TST_DESC1 = "Test key 2";
static const char* K_TST_PRIV1="aabbaabbaabc";
static const char* K_TST_PUBL1="ccddccddccde";
static const char* K_TST_SECU1="ddeeddeeddeeddeeddeeddeeddeeddef";
static const int K_TST_CNTR1 = 2;
static const int K_TST_RNDM1 = 12;
static const char* K_TST_DESC2 = "Test key 3";
static const char* K_TST_PRIV2="aabbaabbaabd";
static const char* K_TST_PUBL2="ccddccddccdf";
static const char* K_TST_SECU2="ddeeddeeddeeddeeddeeddeeddeeddec";
static const int K_TST_CNTR2 = 3;
static const int K_TST_RNDM2 = 13;

TEST_F(TestKeyListPresenter,canReadTheConfigDir) {
	BOOST_LOG_NAMED_SCOPE(
			"TestKeyListPresenter_canReadTheConfigDir_Test::TestBody");
	path myTestCfgFile(unique_path("/tmp/trihlav-tests-%%%%-%%%%"));
	EXPECT_FALSE(exists(myTestCfgFile));
	EXPECT_TRUE(create_directory(myTestCfgFile));
	BOOST_LOG_TRIVIAL(debug)<< "Test data location: " << myTestCfgFile <<".";
	NiceMock<MockFactory> myMockFactory;
	KeyManager& myKeyMan(myMockFactory.getKeyManager());
	myKeyMan.setConfigDir(myTestCfgFile);
	YubikoOtpKeyConfig myCfg0(myKeyMan), myCfg1(myKeyMan), myCfg2(myKeyMan);
	myCfg0.setDescription(K_TST_DESC0);
	myCfg0.setPrivateId(K_TST_PRIV0);
	myCfg0.setPublicId(K_TST_PUBL0);
	myCfg0.setCounter(K_TST_CNTR0);
	myCfg0.setRandom(K_TST_RNDM0);
	myCfg0.setSecretKey(K_TST_SECU0);
	myCfg0.save();
	myCfg1.setDescription(K_TST_DESC1);
	myCfg1.setPrivateId(K_TST_PRIV1);
	myCfg1.setPublicId(K_TST_PUBL1);
	myCfg1.setCounter(K_TST_CNTR1);
	myCfg1.setRandom(K_TST_RNDM1);
	myCfg1.setSecretKey(K_TST_SECU1);
	myCfg1.save();
	myCfg2.setDescription(K_TST_DESC2);
	myCfg2.setPrivateId(K_TST_PRIV2);
	myCfg2.setPublicId(K_TST_PUBL2);
	myCfg2.setCounter(K_TST_CNTR2);
	myCfg2.setRandom(K_TST_RNDM2);
	myCfg2.setSecretKey(K_TST_SECU2);
	myCfg2.save();
	myKeyMan.loadKeys();
	EXPECT_EQ(3,myKeyMan.getKeyCount());
	const YubikoOtpKeyConfig& myCfg01(*myKeyMan.getKeyByPublicId(myCfg0.getPublicId()));
	const YubikoOtpKeyConfig& myCfg11(*myKeyMan.getKeyByPublicId(myCfg1.getPublicId()));
	const YubikoOtpKeyConfig& myCfg21(*myKeyMan.getKeyByPublicId(myCfg2.getPublicId()));
	EXPECT_EQ(myCfg0,myCfg01);
	EXPECT_EQ(myCfg1,myCfg11);
	EXPECT_EQ(myCfg2,myCfg21);

	EXPECT_EQ(K_TST_DESC0, myCfg01.getDescription());
	EXPECT_EQ(K_TST_PRIV0, myCfg01.getPrivateId());
	EXPECT_EQ(K_TST_PUBL0, myCfg01.getPublicId());
	EXPECT_EQ(K_TST_CNTR0, myCfg01.getCounter());
	EXPECT_EQ(K_TST_RNDM0, myCfg01.getRandom());
	EXPECT_EQ(K_TST_SECU0, myCfg01.getSecretKey());

	EXPECT_EQ(K_TST_DESC1, myCfg11.getDescription());
	EXPECT_EQ(K_TST_PRIV1, myCfg11.getPrivateId());
	EXPECT_EQ(K_TST_PUBL1, myCfg11.getPublicId());
	EXPECT_EQ(K_TST_CNTR1, myCfg11.getCounter());
	EXPECT_EQ(K_TST_RNDM1, myCfg11.getRandom());
	EXPECT_EQ(K_TST_SECU1, myCfg11.getSecretKey());

	EXPECT_EQ(K_TST_DESC2, myCfg21.getDescription());
	EXPECT_EQ(K_TST_PRIV2, myCfg21.getPrivateId());
	EXPECT_EQ(K_TST_PUBL2, myCfg21.getPublicId());
	EXPECT_EQ(K_TST_CNTR2, myCfg21.getCounter());
	EXPECT_EQ(K_TST_RNDM2, myCfg21.getRandom());
	EXPECT_EQ(K_TST_SECU2, myCfg21.getSecretKey());

	remove_all(myTestCfgFile);
	EXPECT_FALSE(exists(myTestCfgFile));
}

int main(int argc, char **argv) {
	initLog();
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}

