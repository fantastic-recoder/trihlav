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
#include <boost/locale.hpp>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WBootstrapTheme.h>

#include "trihlavLib/trihlavLogApi.hpp"

#include "trihlavWtMainPanelView.hpp"
#include "trihlavApp.hpp"
#include "trihlavLib/trihlavMainPanelPresenter.hpp"
#include "trihlavLib/trihlavGetUiFactory.hpp"

using namespace Wt;
using boost::locale::translate;

namespace trihlav {

    App::App(const WEnvironment &pEnv) :
            WApplication(pEnv) //
    {
        setTitle("TRIHLAV");               // application title
/*        std::shared_ptr<WBootstrapTheme> bootstrapTheme(new WBootstrapTheme());
        setTheme(bootstrapTheme);
        useStyleSheet("style/trihlav.css");
        m_MainPanelCntrl = std::make_unique<MainPanelPresenter>(getUiFactory());
        trihlav::ViewIface &myIMainPanelView = m_MainPanelCntrl->getView();
        auto &myMainPanelView = dynamic_cast<WtMainPanelView &>
        (myIMainPanelView);
        root()->addWidget(std::unique_ptr<Wt::WWidget>(myMainPanelView.getContentsStackWgt()));
        m_MainPanelCntrl->setupUi();*/
        BOOST_LOG_TRIVIAL(info) << "App created.";
    }

    AppPtr App::createApplication(const WEnvironment &env) {
        /*
         * You could read information from the environment to decide whether
         * the user has permission to start a new application
         */
        return std::unique_ptr<App>(new App(env));
    }

    App::~App() {
        BOOST_LOG_NAMED_SCOPE("App::~App()");
    }

} /* namespace trihlav */
