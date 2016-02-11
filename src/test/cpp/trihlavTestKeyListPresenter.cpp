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

#include "../../main/cpp/trihlavLib/trihlavYubikoOtpKeyPresenterI.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavLib/trihlavLog.hpp"
#include "trihlavLib/trihlavIButton.hpp"
#include "trihlavLib/trihlavIFactory.hpp"
#include "trihlavLib/trihlavIKeyListView.hpp"
#include "trihlavLib/trihlavKeyListPresenter.hpp"
#include "trihlavLib/trihlavIYubikoOtpKeyView.hpp"

#include "trihlavMockButton.hpp"
#include "trihlavMockStrEdit.hpp"
#include "trihlavMockSpinBox.hpp"
#include "trihlavMockFactory.hpp"
#include "trihlavMockYubikoOtpKeyView.hpp"
#include "trihlavMockYubikoOtpKeyPresenter.hpp"
#include "trihlavMockKeyListView.hpp"

#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
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
	EXPECT_CALL(myMockFactory, createYubikoOtpKeyPresenter()) //
	.WillOnce(Return(new YubikoOtpKeyPresenter(myMockFactory)));

	KeyListPresenter myKeyListPresenter(myMockFactory);
	YubikoOtpKeyPresenterI& myYubikoOtpKeyPresenter =
			myKeyListPresenter.getYubikoOtpKeyPresenter();
	IYubikoOtpKeyView& myView = myYubikoOtpKeyPresenter.getView();
	MockYubikoOtpKeyView& myMockYubikoOtpKeyView =
			reinterpret_cast<MockYubikoOtpKeyView&>(myView);
	IKeyListView& myKeyListView = myKeyListPresenter.getView();
	//EXPECT_CALL(myMockYubikoOtpKeyView, show());
	myKeyListView.getBtnAddKey().getPressedSignal()();
}

int main(int argc, char **argv) {
	initLog();
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}

