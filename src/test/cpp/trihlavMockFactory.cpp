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

#include <memory>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavMockFactory.hpp"

#include "trihlavLib/trihlavKeyListViewIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyViewIface.hpp"
#include "trihlavLib/trihlavOsIface.hpp"
#include "trihlavLib/trihlavSysUserListViewIface.hpp"
#include "trihlavLib/trihlavLoginViewIface.hpp"
#include "trihlavLib/trihlavMainPanelViewIface.hpp"
#include "trihlavLib/trihlavKeyListPresenterIface.hpp"

#include "trihlavMockYubikoOtpKeyView.hpp"
#include "trihlavMockKeyListView.hpp"
#include "trihlavMockMessageView.hpp"
#include "trihlavMockPswdCheckView.hpp"
#include "trihlavMockLoginView.hpp"

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::NiceMock;
using ::testing::DoAll;
using ::testing::Invoke;

namespace trihlav {

MockFactory::MockFactory() {
	BOOST_LOG_NAMED_SCOPE("MockFactory::MockFactory");

	ON_CALL(*this, createYubikoOtpKeyView()) //
	.WillByDefault(Invoke([]()->YubikoOtpKeyViewIfacePtr //
			{
				BOOST_LOG_NAMED_SCOPE("MockFactory::createYubikoOtpKeyView");
				auto myRetVal=new NiceMock<MockYubikoOtpKeyView>;
				myRetVal->setupDefaultOnCallHandlers();
				BOOST_LOG_TRIVIAL(debug)<< "Created " << myRetVal;
				return YubikoOtpKeyViewIfacePtr(myRetVal);
			}));

	ON_CALL(*this, createKeyListView()) //
	.WillByDefault(Invoke([]()->KeyListViewIfacePtr //
			{
				BOOST_LOG_NAMED_SCOPE("MockFactory::createKeyListView");
				auto myRetVal=new NiceMock<MockKeyListView>;
				BOOST_LOG_TRIVIAL(debug)<< "Created " << myRetVal;
				return KeyListViewIfacePtr(myRetVal);
			}));

	ON_CALL(*this, createMessageView()) //
	.WillByDefault(Invoke([]()->MessageViewIfacePtr //
			{
				BOOST_LOG_NAMED_SCOPE("MockFactory::createMessageView");
				auto myRetVal=new NiceMock<MockMessageView>;
				BOOST_LOG_TRIVIAL(debug)<< "Created " << myRetVal;
				return MessageViewIfacePtr(myRetVal);
			}));

	ON_CALL(*this, createPswdChckView()) //
	.WillByDefault(Invoke([]()->PswdChckViewIfacePtr //
			{
				BOOST_LOG_NAMED_SCOPE("MockFactory::createPswdChckView");
				auto myRetVal=new NiceMock<MockPswdCheckView>;
				BOOST_LOG_TRIVIAL(debug)<< "Created " << myRetVal;
				return PswdChckViewIfacePtr(myRetVal);
			}));
	ON_CALL(*this, createLoginView()) //
            .WillByDefault(Invoke([]() -> LoginViewIfacePtr //
			{
				BOOST_LOG_NAMED_SCOPE("MockFactory::createLoginView");
				auto myRetVal=new NiceMock< MockLoginView>;
				BOOST_LOG_TRIVIAL(debug)<< "Created mock login view." << myRetVal;
                return LoginViewIfacePtr(myRetVal);
			}));
	ON_CALL(*this, getOsIface()) //
	.WillByDefault(Invoke([this]()->OsIface& //
			{
				return this->m_MockOs;
			}));
}

}  // namespace trihlav
