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

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavMockYubikoOtpKeyView.hpp"

using ::testing::Return;
using ::testing::ReturnRef;

namespace trihlav {

MockYubikoOtpKeyView::MockYubikoOtpKeyView() {
	BOOST_LOG_NAMED_SCOPE("MockYubikoOtpKeyView::MockYubikoOtpKeyView");

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

MockYubikoOtpKeyView::~MockYubikoOtpKeyView() {
	BOOST_LOG_NAMED_SCOPE("MockYubikoOtpKeyView::~MockYubikoOtpKeyView");
}

}  // namespace trihlav
