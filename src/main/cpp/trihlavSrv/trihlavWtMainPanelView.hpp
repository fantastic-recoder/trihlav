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
#include "trihlavLib/trihlavIMainPanelView.hpp"

namespace Wt {
class WContainerWidget;
class WNavigationBar;
class WMenu;
}

namespace trihlav {

/**
 * WT++ implementation of IMainPanelView.
 */
class WtMainPanelView: virtual public IMainPanelView {
public:
	WtMainPanelView();
	virtual ~WtMainPanelView();
	virtual Wt::WContainerWidget* getNativeView();
	virtual void setupUi();
	virtual void add(const std::string& pName, IPswdChckView& pPswdChckView);

	const Wt::WNavigationBar* getNavigation() const {
		return itsNavigation;
	}

	void setNavigation(Wt::WNavigationBar* pNavigation) {
		itsNavigation = pNavigation;
	}

	const Wt::WMenu* getLeftMenu() const {
		return itsLeftMenu;
	}

	Wt::WMenu* getLeftMenu() {
		return itsLeftMenu;
	}

	void setLeftMenu(Wt::WMenu* pLeftMenu) {
		itsLeftMenu = pLeftMenu;
	}

private:
	Wt::WContainerWidget* itsView;
	Wt::WNavigationBar* itsNavigation;
	Wt::WMenu* itsLeftMenu;
};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_MAIN_PANEL_VIEW_HPP_ */
