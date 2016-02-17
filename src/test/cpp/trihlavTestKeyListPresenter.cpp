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

#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavLib/trihlavLog.hpp"
#include "trihlavLib/trihlavIButton.hpp"
#include "trihlavLib/trihlavIFactory.hpp"
#include "trihlavLib/trihlavIKeyListView.hpp"
#include "trihlavLib/trihlavKeyListPresenter.hpp"
#include "trihlavLib/trihlavIYubikoOtpKeyView.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"

#include "trihlavMockButton.hpp"
#include "trihlavMockStrEdit.hpp"
#include "trihlavMockSpinBox.hpp"
#include "trihlavMockFactory.hpp"
#include "trihlavMockYubikoOtpKeyView.hpp"
#include "trihlavMockKeyListView.hpp"

#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavMockEditI.hpp"

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
	IYubikoOtpKeyView& myView(*myYubikoOtpKeyPresenter.getView());
	MockYubikoOtpKeyView& myMockYubikoOtpKeyView =
			dynamic_cast<MockYubikoOtpKeyView&>(myView);
	IKeyListView& myKeyListView = myKeyListPresenter.getView();
	EXPECT_CALL(myMockYubikoOtpKeyView, show());
	myKeyListView.getBtnAddKey().getPressedSignal()();
}

TEST_F(TestKeyListPresenter,canReadTheConfigDir) {
	BOOST_LOG_NAMED_SCOPE("TestKeyListPresenter_canReadTheConfigDir_Test::TestBody");
	path myTestCfgFile(unique_path("/tmp/trihlav-tests-%%%%-%%%%"));
	EXPECT_FALSE(exists(myTestCfgFile));
	EXPECT_TRUE(create_directory(myTestCfgFile));
	BOOST_LOG_TRIVIAL(debug)<< "Test data location: '" << myTestCfgFile <<"'.";
	NiceMock<MockFactory> myMockFactory;
	myMockFactory.getKeyManager().setConfigDir(myTestCfgFile);
	YubikoOtpKeyConfig myCfg0(myMockFactory.getKeyManager()),
			myCfg1(myMockFactory.getKeyManager()),
			myCfg2(myMockFactory.getKeyManager());
	myCfg0.setDescription("Test key 1");
	myCfg0.setPrivateId("aabbaabbaabb");
	myCfg0.setPublicId("ccddccddccdd");
	myCfg0.setCounter(1);
	myCfg0.setRandom(11);
	myCfg0.setSecretKey("ddeeddeeddeeddeeddeeddeeddeeddee");
	remove_all(myTestCfgFile);
	EXPECT_FALSE(exists(myTestCfgFile));
}

int main(int argc, char **argv) {
	initLog();
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}

