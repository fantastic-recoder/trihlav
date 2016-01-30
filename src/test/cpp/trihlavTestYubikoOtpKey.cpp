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

class StrEditMock: public IStrEdit {
public:
	std::string val;
	StrEditMock() {}
	StrEditMock(const StrEditMock& ) {}

	virtual const std::string getValue() const { return val; }

	virtual void setValue(const std::string& pVal) {
		val=pVal;
	}


};

class MockIButton : public IButton {
public:
	std::string val;
	virtual const std::string getText() const { return val; }

	virtual void setText( const std::string& pVal) {
		val=pVal;
	}
};

class MockYubikoOtpKeyView: public IYubikoOtpKeyView {
public:
	StrEditMock itsPrivateIdEditMock;
	StrEditMock itsPublicIdEditMock;
	StrEditMock itsSecretKeyEditMock;
	StrEditMock itsPublicIdLenEditMock;
	MockIButton itsGenPrivateIdMock;
	MockIButton  itsGenPublicIdMock;
	MockIButton  itsGenSecretKeyMock;
	MockIButton  itsMockSaveBtn;
	MockIButton  itsCancelButtonMock;
	MockYubikoOtpKeyView() {
		ON_CALL(*this,getPrivateId()) //
		.WillByDefault(ReturnRef(itsPrivateIdEditMock));

		ON_CALL(*this,getSecretKey()) //
		.WillByDefault(ReturnRef(itsSecretKeyEditMock));

		ON_CALL(*this,getPublicId()) //
		.WillByDefault(ReturnRef(itsPublicIdEditMock));

		ON_CALL(*this,getPublicIdLen()) //
		.WillByDefault(ReturnRef(itsPublicIdLenEditMock));

		ON_CALL(*this,getSaveBtn()) //
		.WillByDefault(ReturnRef(itsMockSaveBtn));

	}
	MOCK_CONST_METHOD0( getPublicId, IStrEdit& () );
	MOCK_METHOD0(getPublicId,IStrEdit& () );

	MOCK_METHOD0(getPublicIdLen, IStrEdit& () );
	MOCK_CONST_METHOD0(getPublicIdLen, IStrEdit& () );

	MOCK_CONST_METHOD0(getPrivateId, IStrEdit& () );
	MOCK_METHOD0(getPrivateId, IStrEdit& () );

	MOCK_CONST_METHOD0(getSecretKey, IStrEdit& () );
	MOCK_METHOD0(getSecretKey, IStrEdit& () );

	MOCK_CONST_METHOD0(getGenPublicIdentityBtn, IButton& () );
	MOCK_METHOD0(getGenPublicIdentityBtn, IButton& () );

	MOCK_CONST_METHOD0(getGenPrivateIdentityBtn, IButton& () );
	MOCK_METHOD0(getGenPrivateIdentityBtn, IButton& () );

	MOCK_CONST_METHOD0(getGenSecretKeyBtn, IButton& () );
	MOCK_METHOD0(getGenSecretKeyBtn, IButton& () );

	MOCK_CONST_METHOD0(getCancelBtn, IButton& () );
	MOCK_METHOD0(getCancelBtn, IButton& () );

	MOCK_CONST_METHOD0(getSaveBtn, IButton& () );
	MOCK_METHOD0(getSaveBtn, IButton& () );

	MOCK_METHOD0(show, void ());

};

class MockFactory: public IFactory {
	MockYubikoOtpKeyView itsMockYubikoOtpKeyView;
public:
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
	MockYubikoOtpKeyView& myYubikoOtpKeyView(myMockFactory.getYubikoOtpKeyView());
	EXPECT_TRUE(myYubikoOtpKeyView.itsPrivateIdEditMock.getValue().empty());
	EXPECT_TRUE(myYubikoOtpKeyView.itsPublicIdEditMock.getValue().empty());
	EXPECT_EQ(myYubikoOtpKeyView.itsPublicIdLenEditMock.getValue(),"6");
	EXPECT_TRUE(remove_all(myKManPath));
	BOOST_LOG_TRIVIAL(debug)<< "testKeyManager OK";
}

TEST(trihlavYubikoOtpKey,generateBtnsFcionality) {
	BOOST_LOG_NAMED_SCOPE("testGenerateButtons");
	MockFactory myMockFactory;
	YubikoOtpKeyPresenter myPresenter(myMockFactory);
}

