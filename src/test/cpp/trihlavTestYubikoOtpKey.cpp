#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavGlobalFixture.hpp"
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

using namespace std;
using namespace trihlav;
using namespace boost;
using namespace boost::filesystem;

using ::testing::Return;
using ::testing::ReturnRef;

string thePrivateIdStr("666");
string thePublicIdStr("666");
string theSecretKeyStr("666");
int thePublicIdLen = 666;

template<typename T>
struct IMockEdit: virtual public IEdit<T> {
	T itsVal;

	/**
	 * @brief Getter
	 * @return a copy of it's value
	 */
	virtual const T getValue() const {
		return itsVal;
	}

	/**
	 * @brief Just sets the internal value.
	 * @see IStrEdit::getValue
	 * @return void
	 */
	virtual void setValue(const T& pVal) {
		itsVal = pVal;
	}

};

struct MockStrEdit: virtual public IMockEdit<std::string>, virtual public IStrEdit {
};

struct MockSpinBox: virtual public IMockEdit<int>, virtual public ISpinBox {
	int itsMin;
	int itsMax;
	int itsStep;

	/**
	 * Set some unlikely initialization values like min = -1, max = -1 und
	 * step = 0.
	 */
	MockSpinBox():itsMin(-1),itsMax(-1),itsStep(0) {
	}

	virtual const int getValue() const {
		return IMockEdit<int>::getValue();
	}

	virtual void setValue(const int& pVal) {
		IMockEdit<int>::setValue(pVal);
	}

	virtual void setMin(const int pMin) {
		itsMin = pMin;
	}

	virtual const int getMin() const {
		return itsMin;
	}

	virtual void setMax(const int pMax) {
		itsMax = pMax;
	}

	virtual const int getMax() const {
		return itsMax;
	}

	virtual void setStep(const int pStep) {
		itsStep = pStep;
	}

	virtual const int getStep() const {
		return itsStep;
	}

};

struct MockButton: public IButton {
	std::string itsVal;
	virtual const std::string getText() const {
		return itsVal;
	}

	virtual void setText(const std::string& pVal) {
		itsVal = pVal;
	}
};

struct MockYubikoOtpKeyView: public IYubikoOtpKeyView {

	MockStrEdit itsMockEdtPrivateId;
	MockStrEdit itsMockEdtPublicId;
	MockStrEdit itsMockEdtDescription;
	MockStrEdit itsMockEdtSecretKey;
	MockSpinBox itsMockSbxPublicIdLen;
	MockButton itsMockBtnGenPrivateId;
	MockButton itsMockBtnGenPublicId;
	MockButton itsMockBtnGenSecretKey;
	MockButton itsMockBtnSave;
	MockButton itsMockBtnCancel;

	MockYubikoOtpKeyView() {
		ON_CALL(*this,getEdtPrivateId()) //
		.WillByDefault(ReturnRef(itsMockEdtPrivateId));

		ON_CALL((const MockYubikoOtpKeyView&)(*this),getEdtPrivateId()) //
		.WillByDefault(ReturnRef(itsMockEdtPrivateId));

		ON_CALL(*this,getEdtSecretKey()) //
		.WillByDefault(ReturnRef(itsMockEdtSecretKey));

		ON_CALL((const MockYubikoOtpKeyView&)(*this),getEdtSecretKey()) //
		.WillByDefault(ReturnRef(itsMockEdtSecretKey));

		ON_CALL(*this,getEdtPublicId()) //
		.WillByDefault(ReturnRef(itsMockEdtPublicId));

		ON_CALL((const MockYubikoOtpKeyView&)(*this),getEdtPublicId()) //
		.WillByDefault(ReturnRef(itsMockEdtPublicId));

		ON_CALL(*this,getEdtDescription()) //
		.WillByDefault(ReturnRef(itsMockEdtDescription));

		ON_CALL((const MockYubikoOtpKeyView&)(*this),getEdtDescription()) //
		.WillByDefault(ReturnRef(itsMockEdtDescription));

		ON_CALL(*this,getSbxPublicIdLen()) //
		.WillByDefault(ReturnRef(itsMockSbxPublicIdLen));

		ON_CALL((const MockYubikoOtpKeyView&)(*this),getSbxPublicIdLen()) //
		.WillByDefault(ReturnRef(itsMockSbxPublicIdLen));

		ON_CALL(*this,getSbxPublicIdLen()) //
		.WillByDefault(ReturnRef(itsMockSbxPublicIdLen));

		ON_CALL(*this,getBtnSave()) //
		.WillByDefault(ReturnRef(itsMockBtnSave));

		ON_CALL(*this,getBtnGenPrivateId()) //
		.WillByDefault(ReturnRef(itsMockBtnGenPrivateId));

		ON_CALL(*this,getBtnGenPublicId()) //
		.WillByDefault(ReturnRef(itsMockBtnGenPublicId));

		ON_CALL(*this,getBtnGenSecretKey()) //
		.WillByDefault(ReturnRef(itsMockBtnGenSecretKey));

	}
	MOCK_CONST_METHOD0( getEdtPublicId, const IStrEdit& () );
	MOCK_METHOD0(getEdtPublicId,IStrEdit& () );

	MOCK_METHOD0(getSbxPublicIdLen, ISpinBox& () );
	MOCK_CONST_METHOD0(getSbxPublicIdLen, const ISpinBox& () );

	MOCK_CONST_METHOD0(getEdtPrivateId, const  IStrEdit& () );
	MOCK_METHOD0(getEdtPrivateId, IStrEdit& () );

	MOCK_CONST_METHOD0(getEdtSecretKey, const  IStrEdit& () );
	MOCK_METHOD0(getEdtSecretKey, IStrEdit& () );

	MOCK_CONST_METHOD0(getEdtDescription, const  IStrEdit& () );
	MOCK_METHOD0(getEdtDescription, IStrEdit& () );

	MOCK_CONST_METHOD0(getBtnGenPublicId, const  IButton& () );
	MOCK_METHOD0(getBtnGenPublicId, IButton& () );

	MOCK_CONST_METHOD0(getBtnGenPrivateId, const  IButton& () );
	MOCK_METHOD0(getBtnGenPrivateId, IButton& () );

	MOCK_CONST_METHOD0(getBtnGenSecretKey, const  IButton& () );
	MOCK_METHOD0(getBtnGenSecretKey, IButton& () );

	MOCK_CONST_METHOD0(getBtnCancel,  const IButton& () );
	MOCK_METHOD0(getBtnCancel, IButton& () );

	MOCK_CONST_METHOD0(getBtnSave, const  IButton& () );
	MOCK_METHOD0(getBtnSave, IButton& () );

	MOCK_METHOD0(show, void ());

};

/**
 * @brief Mock factory.
 * It returns mock implementations. It has only
 * singleton objects, so consequent execution of the same createXXX 
 * method returns same object.
 */
struct MockFactory: public IFactory {
	MockYubikoOtpKeyView itsMockYubikoOtpKeyView;

	MOCK_CONST_METHOD0(createMainPanelView,IMainPanelView* ());
	MOCK_CONST_METHOD0(createKeyListPresenter,IKeyListPresenter* () );
	MOCK_CONST_METHOD0(createKeyListView,IKeyListView* () );
	MOCK_CONST_METHOD0(createPswdChckPresenter,IPswdChckPresenter* () );
	MOCK_CONST_METHOD0(createYubikoOtpKeyPresenter,IYubikoOtpKeyPresenter* ());
	MOCK_CONST_METHOD0(createPswdChckView,IPswdChckView* () );
	MOCK_CONST_METHOD0(createYubikoOtpKeyView,IYubikoOtpKeyView* () );

	MockFactory() {
		ON_CALL(*this,createYubikoOtpKeyView()) //
		.WillByDefault(Return(&itsMockYubikoOtpKeyView));
	}

	MockYubikoOtpKeyView& getYubikoOtpKeyView() {
		return itsMockYubikoOtpKeyView;
	}
};

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
	MockYubikoOtpKeyView& myYubikoOtpKeyView(
			myMockFactory.getYubikoOtpKeyView());
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
	MockYubikoOtpKeyView& myYubikoOtpKeyView(
			myMockFactory.getYubikoOtpKeyView());
	EXPECT_CALL(myYubikoOtpKeyView,show());
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
	const path myFilename(myCfg->getFilename());
	BOOST_LOG_TRIVIAL(debug)<< "0 myPrivId   : "<< myPrivId << ".";
	BOOST_LOG_TRIVIAL(debug)<< "0 myPublicId : "<< myPublicId << ".";
	BOOST_LOG_TRIVIAL(debug)<< "0 mySecretKey: "<< mySecretKey<< ".";
	BOOST_LOG_TRIVIAL(debug)<< "1 myPrivId   : "<< myCfg->getPrivateId() << ".";
	BOOST_LOG_TRIVIAL(debug)<< "1 myPublicId : "<< myCfg->getPublicId() << ".";
	BOOST_LOG_TRIVIAL(debug)<< "1 mySecretKey: "<< myCfg->getSecretKey() << ".";
	EXPECT_TRUE(!myCfg->getPrivateId().empty());
	EXPECT_TRUE(!myCfg->getPublicId().empty());
	EXPECT_TRUE(!myCfg->getSecretKey().empty());
	EXPECT_TRUE(myPublicId.compare(myCfg->getPublicId()) == 0);
	EXPECT_TRUE(myPrivId.compare(myCfg->getPrivateId()) == 0);
	EXPECT_TRUE(mySecretKey.compare(myCfg->getSecretKey()) == 0);
	myYubikoOtpKeyPresenter.deleteKey();
	EXPECT_FALSE(exists(myFilename));
}

const int K_TST_STR_L=8;

TEST(trihlavYubikoOtpKey,generateHex) {
	BOOST_LOG_NAMED_SCOPE("generateHex");
	string myTestVal("XXXXXXXXXXXXXXX");
	YubikoOtpKeyPresenter::generate(0,myTestVal);
	EXPECT_EQ(myTestVal.size(),0);
	YubikoOtpKeyPresenter::generate(K_TST_STR_L,myTestVal);
	BOOST_LOG_TRIVIAL(debug)<< "Generated:"<<myTestVal<<".";
	EXPECT_EQ(myTestVal.size(),K_TST_STR_L*2);
}
