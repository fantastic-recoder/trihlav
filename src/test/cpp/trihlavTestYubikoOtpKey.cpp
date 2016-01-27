#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#define BOOST_TEST_MAIN
#define BOOST_REQUIRE_MODULE trihlavYubikoOtpKeyTests
#include <boost/test/included/unit_test.hpp>

#include <FakeIt/single_header/boost/fakeit.hpp>

#include "trihlavGlobalFixture.hpp"
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
using namespace fakeit;

string thePrivateIdStr("666");
string thePublicIdStr("666");
string theSecretKeyStr("666");
int thePublicIdLen = 666;

Mock<IStrEdit> thePrivateIdEditMock;
Mock<IStrEdit> thePublicIdEditMock;
Mock<IStrEdit> theSecretKeyEditMock;
Mock<IStrEdit> thePublicIdLenEditMock;
Mock<IButton> theGenPrivateIdMock;
Mock<IButton> theGenPublicIdMock;
Mock<IButton> theGenSecretKeyMock;
Mock<IButton> theSaveButtonMock;
Mock<IButton> theCancelButtonMock;
Mock<IYubikoOtpKeyView> theMockYubikoOtpKeyView;
Mock<IFactory> theMockFactory;

class InitYoubikoUiMock: virtual public GlobalFixture {
public:
	InitYoubikoUiMock() :
			GlobalFixture() {
		BOOST_LOG_NAMED_SCOPE("InitYoubikoUiMock");
		When(Method(thePrivateIdEditMock,setValue)).AlwaysDo(
				[](const string& pVal) {
					thePrivateIdStr=pVal;
					BOOST_LOG_TRIVIAL(debug)<< "Priv Id == \"" << thePrivateIdStr << "\".";
				});

		When(Method(thePublicIdEditMock,setValue)).AlwaysDo(
				[](const string& pVal) {
					thePublicIdStr=pVal;
					BOOST_LOG_TRIVIAL(debug)<< "Publ Id == \"" << thePublicIdStr << "\".";
				});

		When(Method(theSecretKeyEditMock,setValue)).AlwaysDo(
				[](const string& pVal) {
					theSecretKeyStr =pVal;
					BOOST_LOG_TRIVIAL(debug)<< "Sec Key == \"" << theSecretKeyStr << "\".";
				});

		When(Method(thePublicIdLenEditMock,setValue)).AlwaysDo(
				[](const string& pVal) {
					thePublicIdLen=lexical_cast<int>(pVal);
					BOOST_LOG_TRIVIAL(debug)<< "Id Len == \"" << thePublicIdLen << "\".";
				});

		When(ConstOverloadedMethod( theMockYubikoOtpKeyView, getPublicId, const IStrEdit& () )).AlwaysReturn(
				thePublicIdEditMock.get());
		When(OverloadedMethod( theMockYubikoOtpKeyView, getPublicId, IStrEdit& () )).AlwaysReturn(
				thePublicIdEditMock.get());

		When(ConstOverloadedMethod( theMockYubikoOtpKeyView, getPrivateId, const IStrEdit& () )).AlwaysReturn(
				thePrivateIdEditMock.get());
		When(OverloadedMethod( theMockYubikoOtpKeyView, getPrivateId, IStrEdit& () )).AlwaysReturn(
				thePrivateIdEditMock.get());

		When(ConstOverloadedMethod( theMockYubikoOtpKeyView, getSecretKey, const IStrEdit& () )).AlwaysReturn(
				theSecretKeyEditMock.get());
		When(OverloadedMethod( theMockYubikoOtpKeyView, getSecretKey, IStrEdit& () )).AlwaysReturn(
				theSecretKeyEditMock.get());

		When(ConstOverloadedMethod( theMockYubikoOtpKeyView, getPublicIdLen, const IStrEdit& () )).AlwaysReturn(
				thePublicIdLenEditMock.get());
		When(OverloadedMethod( theMockYubikoOtpKeyView, getPublicIdLen, IStrEdit& () )).AlwaysReturn(
				thePublicIdLenEditMock.get());

		When(ConstOverloadedMethod( theMockYubikoOtpKeyView, getGenPublicIdentityBtn, const IButton& () )).AlwaysReturn(
				theGenPublicIdMock.get());
		When(OverloadedMethod( theMockYubikoOtpKeyView, getGenPublicIdentityBtn, IButton& () )).AlwaysReturn(
				theGenPublicIdMock.get());

		When(ConstOverloadedMethod( theMockYubikoOtpKeyView, getGenPrivateIdentityBtn, const IButton& () )).AlwaysReturn(
				theGenPrivateIdMock.get());
		When(OverloadedMethod( theMockYubikoOtpKeyView, getGenPrivateIdentityBtn, IButton& () )).AlwaysReturn(
				theGenPrivateIdMock.get());

		When(ConstOverloadedMethod( theMockYubikoOtpKeyView, getGenSecretKeyBtn, const IButton& () )).AlwaysReturn(
				theGenSecretKeyMock.get());
		When(OverloadedMethod( theMockYubikoOtpKeyView, getGenSecretKeyBtn, IButton& () )).AlwaysReturn(
				theGenSecretKeyMock.get());

		When(ConstOverloadedMethod( theMockYubikoOtpKeyView, getCancelBtn, const IButton& () )).AlwaysReturn(
				theCancelButtonMock.get());
		When(OverloadedMethod( theMockYubikoOtpKeyView, getCancelBtn, IButton& () )).AlwaysReturn(
				theCancelButtonMock.get());

		When(ConstOverloadedMethod( theMockYubikoOtpKeyView, getSaveBtn, const IButton& () )).AlwaysReturn(
				theSaveButtonMock.get());
		When(OverloadedMethod( theMockYubikoOtpKeyView, getSaveBtn, IButton& () )).AlwaysReturn(
				theSaveButtonMock.get());

		When(ConstOverloadedMethod(theMockFactory,createYubikoOtpKeyView,IYubikoOtpKeyView*())).AlwaysReturn(&theMockYubikoOtpKeyView.get());
	}
};

BOOST_GLOBAL_FIXTURE(InitYoubikoUiMock);

BOOST_AUTO_TEST_SUITE(trihlavTestYubikoOtpKey)

BOOST_AUTO_TEST_CASE(testKeyManagerInitialisation) {
	BOOST_LOG_NAMED_SCOPE("testKeyManagerInitialisation");
	KeyManager myKMan(unique_path("/tmp/trihlav-tst-%%%%-%%%%-%%%%-%%%%"));
	BOOST_LOG_TRIVIAL(debug)<< "Test lazy init. only first getter will cause"
	" initialization";
	BOOST_REQUIRE(!myKMan.isInitialized());
	const path& myKManPath = myKMan.getConfigDir();
	BOOST_LOG_TRIVIAL(debug)<< "Got config. directory \"" << myKManPath << "\","
	" now we should be initialized";

	BOOST_REQUIRE(myKMan.isInitialized());
	BOOST_LOG_TRIVIAL(debug)<< "Does the configuration path exists?";
	BOOST_REQUIRE(exists(myKManPath));
	BOOST_LOG_TRIVIAL(debug)<< "Yes, it does.";

	YubikoOtpKeyPresenter myPresenter(theMockFactory.get());
	// Method(thePrivateIdEditMock,setValue).Using("") does crash - why?
	Verify(Method(thePrivateIdEditMock,setValue)).AtLeastOnce();
	Verify(Method(thePublicIdEditMock,setValue)).AtLeastOnce();
	Verify(Method(thePublicIdLenEditMock,setValue)).AtLeastOnce();
	BOOST_REQUIRE(thePrivateIdStr.empty());
	BOOST_REQUIRE(thePublicIdStr.empty());
	BOOST_REQUIRE(thePublicIdLen == 6);
	BOOST_REQUIRE(remove_all(myKManPath));
	BOOST_LOG_TRIVIAL(debug)<< "testKeyManager OK";
}

BOOST_AUTO_TEST_CASE(testGenerateButtons) {
	BOOST_LOG_NAMED_SCOPE("testGenerateButtons");
	YubikoOtpKeyPresenter myPresenter(theMockFactory.get());
}

BOOST_AUTO_TEST_SUITE_END()
