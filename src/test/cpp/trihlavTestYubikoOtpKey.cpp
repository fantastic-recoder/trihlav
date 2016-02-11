#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavLib/trihlavLog.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavUTimestamp.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavIEdit.hpp"
#include "trihlavLib/trihlavIFactory.hpp"
#include "trihlavLib/trihlavIYubikoOtpKeyView.hpp"
#include "trihlavLib/trihlavIButton.hpp"
#include "trihlavLib/trihlavISpinBox.hpp"

#include "trihlavMockButton.hpp"
#include "trihlavMockEditI.hpp"
#include "trihlavMockStrEdit.hpp"
#include "trihlavMockSpinBox.hpp"
#include "trihlavMockYubikoOtpKeyView.hpp"
#include "trihlavMockYubikoOtpKeyPresenter.hpp"
#include "trihlavMockFactory.hpp"
#include "trihlavMockKeyListView.hpp"

using namespace std;
using namespace trihlav;
using namespace boost;
using namespace boost::filesystem;

string thePrivateIdStr("666");
string thePublicIdStr("666");
string theSecretKeyStr("666");
int thePublicIdLen = 666;

int main(int argc, char **argv) {
	initLog();
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}

TEST(trihlavYubikoOtpKey,keyManagerInit) {
	BOOST_LOG_NAMED_SCOPE("testKeyManagerInitialisation");
	KeyManager myKMan(unique_path("/tmp/trihlav-tst-%%%%-%%%%-%%%%-%%%%"));
	BOOST_LOG_TRIVIAL(debug)<< "Test lazy init. only first getter will cause"
	" initialization";
	EXPECT_TRUE(!myKMan.isInitialized());
	const path& myKManPath = myKMan.getConfigDir();
	BOOST_LOG_TRIVIAL(debug)<< "Got config. directory \"" << myKManPath << "\","
	" now we should be initialized";

	EXPECT_TRUE(myKMan.isInitialized());
	BOOST_LOG_TRIVIAL(debug)<< "Does the configuration path exists?";
	EXPECT_TRUE(exists(myKManPath));
	BOOST_LOG_TRIVIAL(debug)<< "Yes, it does.";

	MockFactory myMockFactory;

	YubikoOtpKeyPresenter myPresenter(myMockFactory);
	MockYubikoOtpKeyView& myYubikoOtpKeyView =
			reinterpret_cast<MockYubikoOtpKeyView&>(myPresenter.getView());
	BOOST_LOG_TRIVIAL(debug)<< "PrivID"  << myYubikoOtpKeyView.itsMockEdtPrivateId.getValue();
	EXPECT_TRUE(myYubikoOtpKeyView.itsMockEdtPrivateId.getValue().empty());
	EXPECT_TRUE(myYubikoOtpKeyView.itsMockEdtPublicId.getValue().empty());
	EXPECT_EQ(myYubikoOtpKeyView.itsMockSbxPublicIdLen.getValue(), 6);
	EXPECT_EQ(myYubikoOtpKeyView.itsMockSbxPublicIdLen.getMin(), 0);
	EXPECT_EQ(myYubikoOtpKeyView.itsMockSbxPublicIdLen.getMax(), 6);
	EXPECT_EQ(myYubikoOtpKeyView.itsMockSbxPublicIdLen.getStep(), 1);
	EXPECT_TRUE(remove_all(myKManPath));
	BOOST_LOG_TRIVIAL(debug)<< "testKeyManager OK";
}

TEST(trihlavYubikoOtpKey,addKeyPressGenerateBtnsDeleteKey) {
	BOOST_LOG_NAMED_SCOPE("testGenerateButtons");
	MockFactory myMockFactory;
	YubikoOtpKeyPresenter myYubikoOtpKeyPresenter(myMockFactory);
	MockYubikoOtpKeyView& myYubikoOtpKeyView =
			reinterpret_cast<MockYubikoOtpKeyView&>(myYubikoOtpKeyPresenter.getView());

	EXPECT_CALL(myYubikoOtpKeyView, show());
	myYubikoOtpKeyPresenter.addKey();
	myYubikoOtpKeyView.itsMockBtnGenPrivateId.getPressedSignal()();
	myYubikoOtpKeyView.itsMockBtnGenPublicId.getPressedSignal()();
	myYubikoOtpKeyView.itsMockBtnGenSecretKey.getPressedSignal()();
	myYubikoOtpKeyView.getAcceptedSignal()(true);
	const string myPrivId(myYubikoOtpKeyView.getEdtPrivateId().getValue());
	const string myPublicId(myYubikoOtpKeyView.getEdtPublicId().getValue());
	const string mySecretKey(myYubikoOtpKeyView.getEdtSecretKey().getValue());
	const int myPubIdLen(myYubikoOtpKeyView.getSbxPublicIdLen().getValue());
	const auto& myCfg = myYubikoOtpKeyPresenter.getCurCfg();
	const path myFilename(myCfg.getFilename());
	BOOST_LOG_TRIVIAL(debug)<< "0 myPrivId   : "<< myPrivId << ".";
	BOOST_LOG_TRIVIAL(debug)<< "0 myPublicId : "<< myPublicId << ".";
	BOOST_LOG_TRIVIAL(debug)<< "0 mySecretKey: "<< mySecretKey<< ".";
	BOOST_LOG_TRIVIAL(debug)<< "1 myPrivId   : "<< myCfg.getPrivateId() << ".";
	BOOST_LOG_TRIVIAL(debug)<< "1 myPublicId : "<< myCfg.getPublicId() << ".";
	BOOST_LOG_TRIVIAL(debug)<< "1 mySecretKey: "<< myCfg.getSecretKey() << ".";
	EXPECT_TRUE(!myCfg.getPrivateId().empty());
	EXPECT_TRUE(!myCfg.getPublicId().empty());
	EXPECT_TRUE(!myCfg.getSecretKey().empty());
	EXPECT_TRUE(myPublicId.compare(myCfg.getPublicId()) == 0);
	EXPECT_TRUE(myPrivId.compare(myCfg.getPrivateId()) == 0);
	EXPECT_TRUE(mySecretKey.compare(myCfg.getSecretKey()) == 0);
	myYubikoOtpKeyPresenter.deleteKey();
	EXPECT_FALSE(exists(myFilename));
}

const int K_TST_STR_L = 8;

TEST(trihlavYubikoOtpKey,generateHex) {
	BOOST_LOG_NAMED_SCOPE("generateHex");
	string myTestVal("XXXXXXXXXXXXXXX");
	YubikoOtpKeyPresenter::generate(0, myTestVal);
	EXPECT_EQ(myTestVal.size(), 0);
	YubikoOtpKeyPresenter::generate(K_TST_STR_L, myTestVal);
	BOOST_LOG_TRIVIAL(debug)<< "Generated:"<<myTestVal<<".";
	EXPECT_EQ(myTestVal.size(), K_TST_STR_L * 2);
}
