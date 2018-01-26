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
#ifndef TRIHLAV_WT_MAIN_PANEL_VIEW_HPP_
#define TRIHLAV_WT_MAIN_PANEL_VIEW_HPP_

#include <string>

#include "../trihlavLib/trihlavMainPanelViewIface.hpp"

namespace Wt {
    class WNavigationBar;

    class WMenu;

    class WStackedWidget;

    class WMenuItem;
}

namespace trihlav {

    class WtViewIface;

/**
 * WT++ implementation of IMainPanelView.
 */
    class WtMainPanelView : virtual public MainPanelViewIface {
    public:
        WtMainPanelView();

        virtual ~WtMainPanelView();

        virtual void
        add(const std::string &pLocalizedName, const PanelName &pName, PswdChckViewIface &pPswdChckView) override;

        virtual void
        add(const std::string &pLocalizedName, const PanelName &pName, KeyListViewIface &pKeyListView) override;

        const Wt::WNavigationBar *getNavigation() const {
            return m_Navigation;
        }

        Wt::WNavigationBar *getNavigation() {
            return m_Navigation;
        }

        const Wt::WStackedWidget *getContentsStack() const {
            return m_ContentsStack;
        }

        Wt::WStackedWidget *getContentsStack() {
            return m_ContentsStack;
        }

        Wt::WWidget *getContentsStackWgt();

        void setContentsStack(Wt::WStackedWidget *myContentsStack) {
            m_ContentsStack = myContentsStack;
        }

        const Wt::WMenu *getLeftMenu() const {
            return m_LeftMenu;
        }

        Wt::WMenu *getLeftMenu() {
            return m_LeftMenu;
        }

    protected:
        virtual void addView(const std::string &pLocalizedName, const PanelName &pName, WtViewIface &pView);

        void setNavigation(Wt::WNavigationBar *pNavigation) {
            m_Navigation = pNavigation;
        }


    private:
        Wt::WStackedWidget *m_MainPanel;
        Wt::WNavigationBar *m_Navigation;
        Wt::WStackedWidget *m_ContentsStack;
        Wt::WMenu *m_LeftMenu;
    };

} /* namespace trihlav */

#endif /* TRIHLAV_WT_MAIN_PANEL_VIEW_HPP_ */
