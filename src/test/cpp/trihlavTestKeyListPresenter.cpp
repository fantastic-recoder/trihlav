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

#include "trihlavLib/trihlavLog.hpp"
#include "trihlavLib/trihlavButtonIface.hpp"
#include "trihlavLib/trihlavFactoryIface.hpp"
#include "trihlavLib/trihlavKeyListViewIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyViewIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavSysUserListViewIface.hpp"
#include "trihlavLib/trihlavMessageViewIface.hpp"
#include "trihlavLib/trihlavKeyListPresenter.hpp"
#include "trihlavLib/trihlavKeyListViewIface.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavOsIface.hpp"
#include "trihlavLib/trihlavSettings.hpp"
#include "trihlavLib/trihlavLoginViewIface.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavMockButton.hpp"
#include "trihlavMockStrEdit.hpp"
#include "trihlavMockSpinBox.hpp"
#include "trihlavMockFactory.hpp"
#include "trihlavMockYubikoOtpKeyView.hpp"
#include "trihlavMockKeyListView.hpp"
#include "trihlavMockMessageView.hpp"
#include "trihlavMockEditIface.hpp"

namespace trihlav {

bool operator==(const KeyListViewIface::KeyRow_t& pLeft,
		const KeyListViewIface::KeyRow_t& pRight) {
	return //
	(std::get < 0 > (pLeft) == std::get < 0 > (pRight)) && //
			(std::get < 1 > (pLeft) == std::get < 1 > (pRight)) && //
			(std::get < 2 > (pLeft) == std::get < 2 > (pRight)) && //
			(std::get < 3 > (pLeft) == std::get < 3 > (pRight)) && //
			(std::get < 4 > (pLeft) == std::get < 4 > (pRight)) && //
			(std::get < 5 > (pLeft) == std::get < 5 > (pRight)) //
	;
}

std::ostream& operator <<(std::ostream& pOstr,
		const KeyListViewIface::KeyRow_t& pRow) {
	pOstr << "KeyListRow{ idx=\"" //
			<< std::get < 0 > (pRow) << "\", pubId=\"" //
			<< std::get < 1 > (pRow) << "\", desc=\"" //
			<< std::get < 2 > (pRow) << "\", key=\"" //
			<< std::get < 3 > (pRow) << "\", use=\"" //
			<< std::get < 4 > (pRow) << "\", cntr=\"" //
			<< std::get < 5 > (pRow) << "}";
	return pOstr;
}
}

using ::std::string;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::Eq;
using ::testing::_;
using ::testing::NiceMock;
using ::trihlav::KeyListViewIface;
//using ::trihlav::operator==;
using ::trihlav::initLog;
using ::trihlav::MockFactory;
using ::trihlav::KeyManager;
using ::trihlav::YubikoOtpKeyConfig;
using ::trihlav::YubikoOtpKeyViewIface;
using ::trihlav::KeyListPresenter;
using ::trihlav::KeyListViewIface;
using ::trihlav::MockKeyListView;
using ::trihlav::YubikoOtpKeyPresenter;
using ::trihlav::MockYubikoOtpKeyView;
using ::trihlav::MockButton;
using ::trihlav::MockMessageView;
using ::boost::filesystem::path;
using ::boost::filesystem::unique_path;

//bool operator== (boost::tuples::tuple<int, std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, int, int>,
//		const boost::tuples::tuple<int, std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, int, int>);

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

TEST_F(TestKeyListPresenter,keyListRow) {
	KeyListViewIface::KeyRow_t r0(0, "1", "2", "3", 4, 5), r1 { r0 };
	EXPECT_TRUE(r0 == r1);
	std::get<1>(r1)= "---";
	EXPECT_FALSE(r0 == r1);
}

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
	myKeyListView.getBtnAddKey().pressedSig();
}

TEST_F(TestKeyListPresenter,buttonsAreInCorrectState) {
	BOOST_LOG_NAMED_SCOPE("TestKeyListPresenter::buttonsAreInCorrectState");
	NiceMock<MockFactory> myMockFactory;
	KeyListPresenter myKeyListPresenter(myMockFactory);
	KeyListViewIface& myView { myKeyListPresenter.getView() };
	myKeyListPresenter.reloadKeyList();
	ASSERT_TRUE(myView.getBtnAddKey().isEnabled());
	ASSERT_FALSE(myView.getBtnDelKey().isEnabled());
	ASSERT_FALSE(myView.getBtnEditKey().isEnabled());
	ASSERT_TRUE(myView.getBtnReload().isEnabled());
}

static const char* K_TST_DESC0 = "Test key 1";
static const char* K_TST_PRIV0 = "aabbaabbaabb";
static const char* K_TST_PUBL0 = "ccddccddccdd";
static const char* K_TST_SECU0 = "ddeeddeeddeeddeeddeeddeeddeeddee";
static const string K_TST_SYS_USER0 { "user0" };
static const int K_TST_CNTR0 = 1;
static const int K_TST_RNDM0 = 11;
static const char* K_TST_DESC1 = "Test key 2";
static const char* K_TST_PRIV1 = "aabbaabbaabc";
static const char* K_TST_PUBL1 = "ccddccddccde";
static const char* K_TST_SECU1 = "ddeeddeeddeeddeeddeeddeeddeeddef";
static const string K_TST_SYS_USER1 { "user1" };
static const int K_TST_CNTR1 = 2;
static const int K_TST_RNDM1 = 12;
static const char* K_TST_DESC2 = "Test key 3";
static const char* K_TST_PRIV2 = "aabbaabbaabd";
static const char* K_TST_PUBL2 = "ccddccddccdf";
static const char* K_TST_SECU2 = "ddeeddeeddeeddeeddeeddeeddeeddec";
static const string K_TST_SYS_USER2 { "user2" };
static const int K_TST_CNTR2 = 3;
static const int K_TST_RNDM2 = 13;

static void createTestKeyConfigs( //
		KeyManager& pKeyMan, //
		YubikoOtpKeyConfig& pCfg0, //
		YubikoOtpKeyConfig& pCfg1, //
		YubikoOtpKeyConfig& pCfg2) {
	BOOST_LOG_NAMED_SCOPE("createTestKeyConfigs");
	pCfg0.setDescription(K_TST_DESC0);
	pCfg0.setPrivateId(K_TST_PRIV0);
	pCfg0.setPublicId(K_TST_PUBL0);
	pCfg0.setCounter(K_TST_CNTR0);
	pCfg0.setRandom(K_TST_RNDM0);
	pCfg0.setSecretKey(K_TST_SECU0);
	pCfg0.setSysUser(K_TST_SYS_USER0);
	pCfg0.save();
	pCfg1.setDescription(K_TST_DESC1);
	pCfg1.setPrivateId(K_TST_PRIV1);
	pCfg1.setPublicId(K_TST_PUBL1);
	pCfg1.setCounter(K_TST_CNTR1);
	pCfg1.setRandom(K_TST_RNDM1);
	pCfg1.setSecretKey(K_TST_SECU1);
	pCfg1.setSysUser(K_TST_SYS_USER1);
	pCfg1.save();
	pCfg2.setDescription(K_TST_DESC2);
	pCfg2.setPrivateId(K_TST_PRIV2);
	pCfg2.setPublicId(K_TST_PUBL2);
	pCfg2.setCounter(K_TST_CNTR2);
	pCfg2.setRandom(K_TST_RNDM2);
	pCfg2.setSecretKey(K_TST_SECU2);
	pCfg2.setSysUser(K_TST_SYS_USER2);
	pCfg2.save();
	pKeyMan.loadKeys();
}

static KeyManager& createKeyManager(NiceMock<MockFactory>& pMockFactory) {
	path myTestCfgFile(unique_path("/tmp/trihlav-tests-%%%%-%%%%"));
	EXPECT_FALSE(exists(myTestCfgFile));
	EXPECT_TRUE(create_directory(myTestCfgFile));
	BOOST_LOG_TRIVIAL(debug)<< "Test data location: " << myTestCfgFile <<".";
	pMockFactory.getSettings().setConfigDir(myTestCfgFile);
	KeyManager& myKeyMan(pMockFactory.getKeyManager());
	return myKeyMan;
}

TEST_F(TestKeyListPresenter,canReadTheConfigDir) {
	BOOST_LOG_NAMED_SCOPE(
			"TestKeyListPresenter_canReadTheConfigDir_Test::TestBody");
	NiceMock<MockFactory> myMockFactory;

	KeyManager& myKeyMan { createKeyManager(myMockFactory) };

	YubikoOtpKeyConfig myCfg0(myKeyMan), myCfg1(myKeyMan), myCfg2(myKeyMan);
	createTestKeyConfigs(myKeyMan, myCfg0, myCfg1, myCfg2);
	EXPECT_EQ(3, myKeyMan.getKeyCount());
	const YubikoOtpKeyConfig& myCfg01(
			*myKeyMan.getKeyByPublicId(myCfg0.getPublicId()));
	const YubikoOtpKeyConfig& myCfg11(
			*myKeyMan.getKeyByPublicId(myCfg1.getPublicId()));
	const YubikoOtpKeyConfig& myCfg21(
			*myKeyMan.getKeyByPublicId(myCfg2.getPublicId()));
	EXPECT_EQ(myCfg0, myCfg01);
	EXPECT_EQ(myCfg1, myCfg11);
	EXPECT_EQ(myCfg2, myCfg21);

	EXPECT_EQ(K_TST_DESC0, myCfg01.getDescription());
	EXPECT_EQ(K_TST_PRIV0, myCfg01.getPrivateId());
	EXPECT_EQ(K_TST_PUBL0, myCfg01.getPublicId());
	EXPECT_EQ(K_TST_CNTR0, myCfg01.getCounter());
	EXPECT_EQ(K_TST_RNDM0, myCfg01.getRandom());
	EXPECT_EQ(K_TST_SECU0, myCfg01.getSecretKey());
	EXPECT_EQ(K_TST_SYS_USER0, myCfg01.getSysUser());

	EXPECT_EQ(K_TST_DESC1, myCfg11.getDescription());
	EXPECT_EQ(K_TST_PRIV1, myCfg11.getPrivateId());
	EXPECT_EQ(K_TST_PUBL1, myCfg11.getPublicId());
	EXPECT_EQ(K_TST_CNTR1, myCfg11.getCounter());
	EXPECT_EQ(K_TST_RNDM1, myCfg11.getRandom());
	EXPECT_EQ(K_TST_SECU1, myCfg11.getSecretKey());
	EXPECT_EQ(K_TST_SYS_USER1, myCfg11.getSysUser());

	EXPECT_EQ(K_TST_DESC2, myCfg21.getDescription());
	EXPECT_EQ(K_TST_PRIV2, myCfg21.getPrivateId());
	EXPECT_EQ(K_TST_PUBL2, myCfg21.getPublicId());
	EXPECT_EQ(K_TST_CNTR2, myCfg21.getCounter());
	EXPECT_EQ(K_TST_RNDM2, myCfg21.getRandom());
	EXPECT_EQ(K_TST_SECU2, myCfg21.getSecretKey());
	EXPECT_EQ(K_TST_SYS_USER2, myCfg21.getSysUser());

	remove_all(myMockFactory.getSettings().getConfigDir());
	EXPECT_FALSE(exists(myMockFactory.getSettings().getConfigDir()));
}

TEST_F(TestKeyListPresenter,canSurviveIllformedKeyfile) {
	BOOST_LOG_NAMED_SCOPE("TestKeyListPresenter::canSurviveIllformedKeyfile");
	NiceMock<MockFactory> myMockFactory;
	KeyManager& myKeyMan { createKeyManager(myMockFactory) };
	YubikoOtpKeyConfig myCfg0(myKeyMan), myCfg1(myKeyMan), myCfg2(myKeyMan);
	createTestKeyConfigs(myKeyMan, myCfg0, myCfg1, myCfg2);
	YubikoOtpKeyConfig myIllCfg(myKeyMan);
	myIllCfg.save();
	myKeyMan.loadKeys();
	EXPECT_EQ(3, myKeyMan.getKeyCount());
	const trihlav::KeyManager::path myConfigDir = myMockFactory.getSettings().getConfigDir();
	BOOST_LOG_TRIVIAL(debug)<< "Clean up. Remove " << myConfigDir;
	remove_all(myConfigDir);
	EXPECT_FALSE(exists(myMockFactory.getSettings().getConfigDir()));

}

TEST_F(TestKeyListPresenter,selectingAKeyAllowsEditButton) {
	BOOST_LOG_NAMED_SCOPE("TestKeyListPresenter::selectingAKeyAllowsEditButton");
	NiceMock<MockFactory> myMockFactory;
	KeyManager& myKeyMan { createKeyManager(myMockFactory) };
	YubikoOtpKeyConfig myCfg0(myKeyMan), myCfg1(myKeyMan), myCfg2(myKeyMan);
	createTestKeyConfigs(myKeyMan, myCfg0, myCfg1, myCfg2);
	BOOST_LOG_TRIVIAL(debug)<<"Going 2 instantiate the presenter";
	KeyListPresenter myKeyListPresenter(myMockFactory);
	BOOST_LOG_TRIVIAL(debug)<<"Preparing expectations.";
	MockKeyListView& myKeyListView =
			dynamic_cast<MockKeyListView&>(myKeyListPresenter.getView());
	const KeyListViewIface::KeyRow_t myRow0 = myKeyListView.createRow(0, myCfg0);
	const KeyListViewIface::KeyRow_t myRow1 = myKeyListView.createRow(1, myCfg1);
	const KeyListViewIface::KeyRow_t myRow2 = myKeyListView.createRow(2, myCfg2);
	MockButton& myDelBtn =
			dynamic_cast<MockButton&>(myKeyListView.getBtnDelKey());
	EXPECT_CALL(myKeyListView, addRow(Eq(myRow0)));
	EXPECT_CALL(myKeyListView, addRow(Eq(myRow1)));
	EXPECT_CALL(myKeyListView, addRow(Eq(myRow2)));
	BOOST_LOG_TRIVIAL(debug)<<"Execute presenter.";
	myKeyListPresenter.reloadKeyList();
	myKeyListView.selectionChangedSig(2);
	EXPECT_TRUE(myDelBtn.isEnabled());
	EXPECT_EQ(3, myKeyMan.getKeyCount());
	remove_all(myMockFactory.getSettings().getConfigDir());
	EXPECT_FALSE(exists(myMockFactory.getSettings().getConfigDir()));
}

TEST_F(TestKeyListPresenter,canEditYubikoKey) {
	BOOST_LOG_NAMED_SCOPE("TestKeyListPresenter::canAddYubikoKey");
	NiceMock<MockFactory> myMockFactory;
	KeyManager& myKeyMan { createKeyManager(myMockFactory) };
	YubikoOtpKeyConfig myCfg0(myKeyMan), myCfg1(myKeyMan), myCfg2(myKeyMan);
	createTestKeyConfigs(myKeyMan, myCfg0, myCfg1, myCfg2);
	BOOST_LOG_TRIVIAL(debug)<<"Going 2 instantiate the presenter";

	KeyListPresenter myKeyListPresenter(myMockFactory);
	YubikoOtpKeyPresenter& myYubikoOtpKeyPresenter =
			myKeyListPresenter.getYubikoOtpKeyPresenter();
	YubikoOtpKeyViewIface& myView(myYubikoOtpKeyPresenter.getView());
	MockYubikoOtpKeyView& myMockYubikoOtpKeyView =
			dynamic_cast<MockYubikoOtpKeyView&>(myView);
	KeyListViewIface& myKeyListView = myKeyListPresenter.getView();
	EXPECT_CALL(myMockYubikoOtpKeyView, show());
	myKeyListView.selectionChangedSig(1);
	myKeyListView.getBtnEditKey().pressedSig();
	remove_all(myMockFactory.getSettings().getConfigDir());
	EXPECT_FALSE(exists(myMockFactory.getSettings().getConfigDir()));
}

TEST_F(TestKeyListPresenter,canDeleteYubikoKey) {
	BOOST_LOG_NAMED_SCOPE("TestKeyListPresenter::canAddYubikoKey");
	NiceMock<MockFactory> myMockFactory;
	KeyManager& myKeyMan { createKeyManager(myMockFactory) };
	YubikoOtpKeyConfig myCfg0(myKeyMan), myCfg1(myKeyMan), myCfg2(myKeyMan);
	createTestKeyConfigs(myKeyMan, myCfg0, myCfg1, myCfg2);
	BOOST_LOG_TRIVIAL(debug)<<"Going 2 instantiate the presenter";

	KeyListPresenter myKeyListPresenter(myMockFactory);
	YubikoOtpKeyPresenter& myYubikoOtpKeyPresenter =
			myKeyListPresenter.getYubikoOtpKeyPresenter();
	YubikoOtpKeyViewIface& myView(myYubikoOtpKeyPresenter.getView());
	MockYubikoOtpKeyView& myMockYubikoOtpKeyView =
			dynamic_cast<MockYubikoOtpKeyView&>(myView);

	MockMessageView& myMockMessageView =
			dynamic_cast<MockMessageView&>(myYubikoOtpKeyPresenter.getMessageView());

	KeyListViewIface& myKeyListView = myKeyListPresenter.getView();
	EXPECT_CALL(myMockMessageView,ask(_,_)).WillOnce(Return(true));
	myKeyListView.selectionChangedSig(1);
	myKeyListView.getBtnDelKey().pressedSig();
	EXPECT_EQ(2, myKeyMan.getKeyCount());
	remove_all(myMockFactory.getSettings().getConfigDir());
	EXPECT_FALSE(exists(myMockFactory.getSettings().getConfigDir()));
}

int main(int argc, char **argv) {
	initLog();
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}

