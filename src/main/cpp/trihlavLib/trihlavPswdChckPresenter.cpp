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

#include <boost/locale.hpp>

#include "trihlavLib/trihlavPswdChckPresenter.hpp"
#include "trihlavLib/trihlavFactoryIface.hpp"
#include "trihlavLib/trihlavPswdChckViewIface.hpp"
#include "trihlavLib/trihlavMessageViewIface.hpp"
#include "trihlavLib/trihlavButtonIface.hpp"

using boost::locale::translate;

namespace trihlav {

PswdChckPresenter::PswdChckPresenter(FactoryIface& pFactory) :
		PswdChckPresenterIface(pFactory), //< forced by virtual inheritance
		PresenterBase(pFactory), //< has a factory
		itsView(0) //< initialize view
{
	BOOST_LOG_NAMED_SCOPE("PswdChckPresenter::PswdChckPresenter");
}

PswdChckViewIface& PswdChckPresenter::getView()
{
	if(!itsView) {
		BOOST_LOG_NAMED_SCOPE("PswdChckPresenter::getView");
		itsView=getFactory().createPswdChckView();
		itsView->getBtnOk().getPressedSignal().connect([=](){okPressed();});
	}
	return *itsView;
}

MessageViewIface& PswdChckPresenter::getMessageView()
{
	if(!itsMessageView) {
		itsMessageView=getFactory().createMessageView();
	}
	return *itsMessageView;
}

void
PswdChckPresenter::okPressed() {
	BOOST_LOG_NAMED_SCOPE("PswdChckPresenter::okPressed");
	getMessageView().showMessage(translate("Trihlav message."),translate("Password not valid."));
}

PswdChckPresenter::~PswdChckPresenter() {
	delete itsView;
	delete itsMessageView;
}

} /* namespace trihlav */
