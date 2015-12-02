#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include <boost/filesystem.hpp>

#define BOOST_TEST_MAIN
#define BOOST_REQUIRE_MODULE trihlavYubikoOtpKeyTests
#include <boost/test/included/unit_test.hpp>


#include <FakeIt/single_header/boost/fakeit.hpp>

#include "trihlavGlobalFixture.hpp"
#include "../../main/cpp/trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavUTimestamp.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavIEdit.hpp"
#include "../../main/cpp/trihlavLib/trihlavIYubikoOtpKeyView.hpp"

using namespace std;
using namespace trihlav;
using namespace boost;
using namespace boost::filesystem;
using namespace fakeit;


string thePrivateIdStr("666");
string thePublicIdStr("666");
string theSecretKeyStr("666");
int thePublicIdLen=666;

Mock<IStrEdit>   thePrivateIdEditMock;
Mock<IStrEdit>   myPublicIdEditMock;
Mock<IStrEdit>   mySecretKeyEditMock;
Mock<IEdit<int>> myPublicIdLenEditMock;
Mock<IButton>    myGenPrivateIdMock;
Mock<IButton>    myGenPublicIdMock;
Mock<IButton>    myGenSecretKeyMock;
Mock<IButton>    mySaveButtonMock;
Mock<IButton>    myCancelButtonMock;

BOOST_GLOBAL_FIXTURE(GlobalFixture);

BOOST_AUTO_TEST_SUITE(trihlavYubikoOtpKeyTests)

BOOST_AUTO_TEST_CASE(testKeyManager) {
	BOOST_LOG_NAMED_SCOPE("testKeyManager");
	KeyManager myKMan(unique_path("/tmp/trihlav-%%%%-%%%%-%%%%-%%%%"));
	BOOST_LOG_TRIVIAL(debug)<< "Test lazy init. only first getter will cause"
	" initalization";
	BOOST_REQUIRE(!myKMan.isInitialized());
	const path& myKManPath = myKMan.getConfigDir();
	BOOST_LOG_TRIVIAL(debug)<< "Got config directory \"" << myKManPath << "\","
	" now we should be initialized";

	BOOST_REQUIRE(myKMan.isInitialized());
	BOOST_REQUIRE(exists(myKManPath));

	When(Method(thePrivateIdEditMock,setValue)).AlwaysDo([](const string& pVal) {
		thePrivateIdStr=pVal;
		BOOST_LOG_TRIVIAL(debug)<< "Priv Id == \"" << thePrivateIdStr << "\".";
	});

	When(Method(myPublicIdEditMock,setValue)).AlwaysDo([](const string& pVal) {
		thePublicIdStr=pVal;
		BOOST_LOG_TRIVIAL(debug)<< "Publ Id == \"" << thePublicIdStr << "\".";
	});

	When(Method(mySecretKeyEditMock,setValue)).AlwaysDo([](const string& pVal) {
		theSecretKeyStr =pVal;
		BOOST_LOG_TRIVIAL(debug)<< "Sec Key == \"" << theSecretKeyStr << "\".";
	});

	When(Method(myPublicIdLenEditMock,setValue)).AlwaysDo([](const int& pVal) {
		thePublicIdLen=pVal;
		BOOST_LOG_TRIVIAL(debug)<< "Id Len == \"" << thePublicIdLen << "\".";
	});

	Mock<IYubikoOtpKeyView> myMockYubikoOtpKeyView;
	When(ConstOverloadedMethod( myMockYubikoOtpKeyView, getPublicId, const IStrEdit& () )).AlwaysReturn(
			myPublicIdEditMock.get());
	When(OverloadedMethod( myMockYubikoOtpKeyView, getPublicId, IStrEdit& () )).AlwaysReturn(
			myPublicIdEditMock.get());

	When(ConstOverloadedMethod( myMockYubikoOtpKeyView, getPrivateId, const IStrEdit& () )).AlwaysReturn(
			thePrivateIdEditMock.get());
	When(OverloadedMethod( myMockYubikoOtpKeyView, getPrivateId, IStrEdit& () )).AlwaysReturn(
			thePrivateIdEditMock.get());

	When(ConstOverloadedMethod( myMockYubikoOtpKeyView, getSecretKey, const IStrEdit& () )).AlwaysReturn(
			mySecretKeyEditMock.get());
	When(OverloadedMethod( myMockYubikoOtpKeyView, getSecretKey, IStrEdit& () )).AlwaysReturn(
			mySecretKeyEditMock.get());

	When(ConstOverloadedMethod( myMockYubikoOtpKeyView, getPublicIdLen, const IEdit<int>& () )).AlwaysReturn(
			myPublicIdLenEditMock.get());
	When(OverloadedMethod( myMockYubikoOtpKeyView, getPublicIdLen, IEdit<int>& () )).AlwaysReturn(
			myPublicIdLenEditMock.get());

	When(ConstOverloadedMethod( myMockYubikoOtpKeyView, getGenPublicIdentityBtn, const IButton& () )).AlwaysReturn(
			myGenPublicIdMock.get());
	When(OverloadedMethod( myMockYubikoOtpKeyView, getGenPublicIdentityBtn, IButton& () )).AlwaysReturn(
			myGenPublicIdMock.get());

	When(ConstOverloadedMethod( myMockYubikoOtpKeyView, getGenPrivateIdentityBtn, const IButton& () )).AlwaysReturn(
			myGenPrivateIdMock.get());
	When(OverloadedMethod( myMockYubikoOtpKeyView, getGenPrivateIdentityBtn, IButton& () )).AlwaysReturn(
			myGenPrivateIdMock.get());

	When(ConstOverloadedMethod( myMockYubikoOtpKeyView, getGenSecretKeyBtn, const IButton& () )).AlwaysReturn(
			myGenSecretKeyMock.get());
	When(OverloadedMethod( myMockYubikoOtpKeyView, getGenSecretKeyBtn, IButton& () )).AlwaysReturn(
			myGenSecretKeyMock.get());

	When(ConstOverloadedMethod( myMockYubikoOtpKeyView, getCancelBtn, const IButton& () )).AlwaysReturn(
			myCancelButtonMock.get());
	When(OverloadedMethod( myMockYubikoOtpKeyView, getCancelBtn, IButton& () )).AlwaysReturn(
			myCancelButtonMock.get());

	When(ConstOverloadedMethod( myMockYubikoOtpKeyView, getSaveBtn, const IButton& () )).AlwaysReturn(
			mySaveButtonMock.get());
	When(OverloadedMethod( myMockYubikoOtpKeyView, getSaveBtn, IButton& () )).AlwaysReturn(
			mySaveButtonMock.get());

	YubikoOtpKeyPresenter myPresenter(myMockYubikoOtpKeyView.get());
	// Method(thePrivateIdEditMock,setValue).Using("") does crash - why?
	Verify(Method(thePrivateIdEditMock,setValue)).AtLeastOnce();
	Verify(Method(myPublicIdEditMock,setValue)).AtLeastOnce();
	Verify(Method(myPublicIdLenEditMock,setValue)).AtLeastOnce();
	BOOST_REQUIRE(thePrivateIdStr.empty());
	BOOST_REQUIRE(thePublicIdStr.empty());
	BOOST_REQUIRE(thePublicIdLen==6);
	BOOST_REQUIRE(remove_all(myKManPath));
	BOOST_LOG_TRIVIAL(debug)<< "testKeyManager ok";
}

BOOST_AUTO_TEST_SUITE_END()
