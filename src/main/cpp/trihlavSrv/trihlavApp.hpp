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
#ifndef TRIHLAV_TRIHLAV_APP_HPP_
#define TRIHLAV_TRIHLAV_APP_HPP_

#include <memory>
#include <map>
#include <string>
#include <Wt/WApplication.h>

namespace Wt {
    class WEnvironment;

    class WLineEdit;

    class WText;
}

namespace trihlav {

    class MainPanelPresenter;

    using AppPtr = std::unique_ptr<Wt::WApplication>;

    extern const std::string K_APP_PATH;

    class App : public Wt::WApplication {
    public:

        App(const Wt::WEnvironment &pEnv);

        virtual ~App();

        bool isAlloved(const std::string &pHostName) const;

        static std::unique_ptr<WApplication> createApplication(const Wt::WEnvironment &pEnv);

    private:
        std::unique_ptr<MainPanelPresenter> m_MainPanelCntrl;
    };

    extern const std::string K_ERROR_PAGE;

} /* namespace trihlav */

#endif /* TRIHLAV_TRIHLAV_APP_HPP_ */
