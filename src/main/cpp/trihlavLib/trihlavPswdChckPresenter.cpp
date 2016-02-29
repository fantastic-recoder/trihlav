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

#include <boost/locale.hpp>

#include <yubikey.h>

#include "trihlavLib/trihlavEditIface.hpp"
#include "trihlavLib/trihlavPswdChckPresenter.hpp"
#include "trihlavLib/trihlavFactoryIface.hpp"
#include "trihlavLib/trihlavPswdChckViewIface.hpp"
#include "trihlavLib/trihlavMessageViewIface.hpp"
#include "trihlavLib/trihlavButtonIface.hpp"

using std::string;
using boost::locale::translate;

namespace trihlav {

PswdChckPresenter::PswdChckPresenter(FactoryIface& pFactory) :
		PswdChckPresenterIface(pFactory), //< forced by virtual inheritance
		PresenterBase(pFactory), //< has a factory
		itsView(0) //< initialize view
{
	BOOST_LOG_NAMED_SCOPE("PswdChckPresenter::PswdChckPresenter");
}

PswdChckViewIface& PswdChckPresenter::getView() {
	if (!itsView) {
		BOOST_LOG_NAMED_SCOPE("PswdChckPresenter::getView");
		itsView = getFactory().createPswdChckView();
		itsView->getBtnOk().getPressedSignal().connect([=]() {okPressed();});
	}
	return *itsView;
}

MessageViewIface& PswdChckPresenter::getMessageView() {
	if (!itsMessageView) {
		itsMessageView = getFactory().createMessageView();
	}
	return *itsMessageView;
}

void PswdChckPresenter::okPressed() {
	BOOST_LOG_NAMED_SCOPE("PswdChckPresenter::okPressed");
	string myPswd0(getView().getEdtPswd0().getValue());
	if (myPswd0.size() < YUBIKEY_OTP_SIZE) {
		getView().getEdtPswd0().setValue("");
		getMessageView().showMessage( //
				translate("Trihlav password check."), //
				translate("Password is too short!"));
		return;
	}
//	yubikey_token_st itsToken;
//	yubikey_parse(reinterpret_cast<uint8_t*>(myOtp0), itsK, &myToken);
//	logDebug_token(myToken);
//	EXPECT_TRUE(myTokenBack.ctr == myToken.ctr);
//	EXPECT_TRUE(myTokenBack.rnd == myToken.rnd);
//	EXPECT_TRUE(myTokenBack.use == myToken.use);
//	EXPECT_TRUE(myTokenBack.tstph == myToken.tstph);
//	EXPECT_TRUE(myTokenBack.tstpl == myToken.tstpl);
//	EXPECT_TRUE(
//			strncmp( reinterpret_cast<const char*>(&myTokenBack.uid),
//					reinterpret_cast<char*>(&myToken.uid), YUBIKEY_UID_SIZE)==0)
//			<< "The uid-s are different!";
//	uint16_t myCrc = yubikey_crc16(reinterpret_cast<uint8_t*>(&myToken),
//	YUBIKEY_KEY_SIZE);
//	BOOST_LOG_TRIVIAL(debug)<< "crc1="<<myCrc <<" - "<<YUBIKEY_CRC_OK_RESIDUE;
//	EXPECT_TRUE(yubikey_crc_ok_p(reinterpret_cast<uint8_t*>(&myToken)))
//			<< "CRC failed!";
	getMessageView().showMessage(translate("Trihlav message."),
			translate("Password is not valid."));
}

PswdChckPresenter::~PswdChckPresenter() {
	delete itsView;
	delete itsMessageView;
}

} /* namespace trihlav */
