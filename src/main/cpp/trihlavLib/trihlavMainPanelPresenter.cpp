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

#include <list>
#include <string>
#include <boost/locale.hpp>

#include "trihlavLib/trihlavLogApi.hpp"
#include "trihlavLib/trihlavMainPanelPresenter.hpp"
#include "trihlavLib/trihlavSettings.hpp"

#include "trihlavFactoryIface.hpp"
#include "trihlavKeyListPresenterIface.hpp"
#include "trihlavMainPanelViewIface.hpp"
#include "trihlavPswdChckPresenterIface.hpp"

using boost::locale::translate;
using std::list;
using std::string;

namespace trihlav {

    MainPanelPresenter::MainPanelPresenter(FactoryIface &pFactory) :
            PresenterBase(pFactory),
            m_KeyListPresenter(pFactory.createKeyListPresenter()),
            m_PswdChckPresenter(pFactory.createPswdChckPresenter()),
            m_MainPanelView(pFactory.createMainPanelView()),
            m_isAthentificated(false) //
    {
        BOOST_LOG_TRIVIAL(debug) << "MainPanelPresenter()";
    }

    MainPanelPresenter::~MainPanelPresenter() {
        BOOST_LOG_TRIVIAL(debug) << "~MainPanelPresenter()";
    }

    ViewIface &MainPanelPresenter::getView() {
        return *m_MainPanelView;
    }

    void MainPanelPresenter::setupUi() {
        getFactory().getSettings().load();
        PswdChckViewIface &myPswdChckView = m_PswdChckPresenter->getView();
        m_MainPanelView->add(translate("Password check"), PanelName::PswdCheck, myPswdChckView);
        KeyListViewIface &myKeyListView = m_KeyListPresenter->getView();
        m_MainPanelView->add(translate("Key list"), PanelName::KeyList, myKeyListView);
        m_MainPanelView->sigShowedPanel.connect([=](const PanelName &pPanel) { showedPanel(pPanel); });
    }

    void MainPanelPresenter::showedPanel(const PanelName pPanel) {
        BOOST_LOG_NAMED_SCOPE("MainPanelPresenter::showedPanel");

        if (pPanel == PanelName::KeyList) {
            m_KeyListPresenter->protectedAction();
        }
    }

    /**
     * Allowed hosts mask can be configured.
     *
     * @param pHostName host name as passed in request.
     *
     * @return true if the host match the mask.
     */
    bool MainPanelPresenter::isAlloved(const std::string &pHostName) {
        list<string> myAllowedHosts{"localhost", "127.0.0.1"};
        for (const string &myAllowedHost : myAllowedHosts) {
            if (pHostName.find(myAllowedHost) == 0) {
                BOOST_LOG_TRIVIAL(debug) << "found " << myAllowedHost << ".";
                return true;
            }
        }
        return false;
    }

} /* namespace trihlav */

