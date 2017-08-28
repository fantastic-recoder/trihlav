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

#include "trihlavLib/trihlavLogApi.hpp"
#include "trihlavLib/trihlavCanOsAuthPresenter.hpp"
#include "trihlavLib/trihlavLoginViewIface.hpp"
#include "trihlavLib/trihlavLoginPresenter.hpp"
#include "trihlavLib/trihlavMessageViewIface.hpp"

namespace trihlav {

CanOsAuthPresenter::CanOsAuthPresenter(FactoryIface& pFactory) :
		PresenterBase(pFactory) {
	// TODO Auto-generated constructor stub

}

CanOsAuthPresenter::~CanOsAuthPresenter() {
	// TODO Auto-generated destructor stub
}

void CanOsAuthPresenter::userAccepted(bool pStatus) {
	BOOST_LOG_NAMED_SCOPE("CanOsAuthPresenter::userAccepted");
	doProtectedAction(pStatus);
}

LoginPresenter& CanOsAuthPresenter::getLoginPresenter() {
	if (!m_LoginPresenter) {
		BOOST_LOG_TRIVIAL(debug)<<"Creating login presenter.";
		m_LoginPresenter.reset(new LoginPresenter(getFactory()));
		m_LoginPresenter->sigUserAccepted.connect(
				[=](bool pStatus)->void {userAccepted(pStatus);});
	}
	BOOST_LOG_TRIVIAL(debug)<<"returning login presenter.";
	return *m_LoginPresenter;
}

void CanOsAuthPresenter::protectedAction() {
	BOOST_LOG_NAMED_SCOPE("CanOsAuthPresenter::protectedAction");
	getLoginPresenter().show();
}

} /* namespace trihlav */
