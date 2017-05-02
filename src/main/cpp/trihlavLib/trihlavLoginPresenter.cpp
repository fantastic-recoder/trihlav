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

#include <boost/locale.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavLib/trihlavEditIface.hpp"
#include "trihlavLib/trihlavMessageViewIface.hpp"
#include "trihlavLib/trihlavFactoryIface.hpp"
#include "trihlavLib/trihlavLoginPresenter.hpp"
#include "trihlavLib/trihlavLoginViewIface.hpp"

using std::string;
using boost::locale::translate;

namespace trihlav {

const std::string LoginPresenter::K_TRIHLAV_OS_PASSWORD_CHECK {
		"Trihlav OS password check." };

LoginPresenter::LoginPresenter(FactoryIface& pFactory) //
:
		PresenterBase(pFactory) //
				, itsOs(pFactory.getOsIface()) {
}

void LoginPresenter::show() {
	BOOST_LOG_NAMED_SCOPE("LoginPresenter::show");
	if (itsStatus != SHOWING) {
		getView().sigDialogFinished.connect( ///< connect start
				[=](bool pStatus)->void
				{	dialogClosed(pStatus);} ///< lambda 2 b called
				);///< end connect
		getView().show();
		BOOST_LOG_TRIVIAL(debug)<<"Showing login dialog ...";
	}
}

LoginViewIface& LoginPresenter::getView() {
	if (!itsLoginView) {
		itsLoginView = getFactory().createLoginView();
	}
	return *itsLoginView;
}

void LoginPresenter::dialogClosed(bool pStatus) {
	BOOST_LOG_NAMED_SCOPE("trihlav::LoginPresenter::dialogClosed");
	if (pStatus) {
		const string myUserName { getView().getEdtUserName().getValue() };
		const string myPassword { getView().getEdtPassword().getValue() };
		if (myUserName.empty()) {
			pStatus = false;
			getMessageView().showMessage(translate(K_TRIHLAV_OS_PASSWORD_CHECK),
					translate("User name is empty."));
		} else if (!itsOs.checkOsPswd(myUserName, myPassword)) {
			pStatus = false;
			itsLoggedInUser = "";
			getMessageView().showMessage(translate(K_TRIHLAV_OS_PASSWORD_CHECK),
					translate(
							"Failed to authenticate the user against the OS."));

		} else {
			itsLoggedInUser = myUserName;
		}
		BOOST_LOG_TRIVIAL(info)<<"User " << myUserName << " accepted.";
	} else {
		BOOST_LOG_TRIVIAL(debug)<<"Password check canceled.";
	}
	sigUserAccepted(pStatus);
	itsStatus = HIDING;
}

MessageViewIface& LoginPresenter::getMessageView() {
	if (!itsMessageView) {
		itsMessageView = getFactory().createMessageView();
	}
	return *itsMessageView;
}

void LoginPresenter::checkUser() {
}

} /* namespace trihlav */

