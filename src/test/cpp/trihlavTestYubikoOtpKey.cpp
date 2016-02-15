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
#include "trihlavMockFactory.hpp"
#include "trihlavMockKeyListView.hpp"

using namespace std;
using namespace trihlav;
using namespace boost;
using namespace boost::filesystem;
using ::testing::NiceMock;

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

struct TestYubikoOtpKey: testing::Test {

};

TEST_F(TestYubikoOtpKey,factoryPointers) {
	BOOST_LOG_NAMED_SCOPE("TestYubikoOtpKey_factoryPointers_Test::TestBody");
	NiceMock<MockFactory> myMockFactory;
	auto myView = myMockFactory.createKeyListView();
	BOOST_LOG_TRIVIAL(debug)<< "YubikoOtpKeyViewPtr:" << myView;
	delete myView;
}

TEST_F(TestYubikoOtpKey,keyManagerInit) {
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

	NiceMock<MockFactory> myMockFactory;
	YubikoOtpKeyPresenter myPresenter(myMockFactory);
	MockYubikoOtpKeyView* myYubikoOtpKeyView(
			dynamic_cast<MockYubikoOtpKeyView*>(myPresenter.getView()));
	BOOST_LOG_TRIVIAL(debug)<< "YubikoOtpKeyView  " << myYubikoOtpKeyView;
	BOOST_LOG_TRIVIAL(debug)<< "PrivateID          '" //
	<< myYubikoOtpKeyView->itsMockEdtPrivateId.getValue() << "'.";
	EXPECT_EQ(myPresenter.getView()->getSbxPublicIdLen().getValue(), 6);
	EXPECT_EQ(myPresenter.getView()->getSbxPublicIdLen().getMin(), 0);
	EXPECT_EQ(myPresenter.getView()->getSbxPublicIdLen().getMax(), 6);
	EXPECT_EQ(myPresenter.getView()->getSbxPublicIdLen().getStep(), 1);
	EXPECT_TRUE(myPresenter.getView()->getEdtPrivateId() .getValue().empty());
	EXPECT_TRUE(myPresenter.getView()->getEdtPublicId().getValue().empty());
	EXPECT_TRUE(remove_all(myKManPath));
	BOOST_LOG_TRIVIAL(debug)<< "testKeyManager OK";
}

TEST_F(TestYubikoOtpKey,addKeyPressGenerateBtnsDeleteKey) {
	BOOST_LOG_NAMED_SCOPE("testGenerateButtons");
	NiceMock<MockFactory> myMockFactory;
	YubikoOtpKeyPresenter myPresenter(myMockFactory);
	IYubikoOtpKeyView* myViewIface(myPresenter.getView());
	MockYubikoOtpKeyView* myYubikoOtpKeyView(
			dynamic_cast<MockYubikoOtpKeyView*>(myPresenter.getView()));
	EXPECT_TRUE(myYubikoOtpKeyView!=0);
	BOOST_LOG_TRIVIAL(debug)<< "Expectations...";
	EXPECT_CALL(*myYubikoOtpKeyView, show());
	BOOST_LOG_TRIVIAL(debug)<< "Expectations set.";
	myPresenter.addKey();
	myViewIface->getBtnGenPrivateId().getPressedSignal()();
	myViewIface->getBtnGenPublicId().getPressedSignal()();
	myViewIface->getBtnGenSecretKey().getPressedSignal()();
	myViewIface->getAcceptedSignal()(true);
	const string myPrivId(myViewIface->getEdtPrivateId().getValue());
	const string myPublicId(myViewIface->getEdtPublicId().getValue());
	const string mySecretKey(myViewIface->getEdtSecretKey().getValue());
	const int myPubIdLen(myViewIface->getSbxPublicIdLen().getValue());
	const auto& myCfg = myPresenter.getCurCfg();
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
	myPresenter.deleteKey();
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
