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
#ifndef TRIHLAV_WT_UI_FACTORY_HPP_
#define TRIHLAV_WT_UI_FACTORY_HPP_

#include "trihlavLib/trihlavFactoryIface.hpp"

namespace trihlav {

class YubikoOtpKeyPresenterIface;

class WtUiFactory: virtual public FactoryIface {
public:
	WtUiFactory();
	virtual ~WtUiFactory();
	virtual MainPanelViewIfacePtr createMainPanelView() override;
	virtual KeyListViewIfacePtr createKeyListView() override;
	virtual PswdChckViewIfacePtr createPswdChckView() override;
	virtual YubikoOtpKeyViewIfacePtr createYubikoOtpKeyView() override;
	virtual MessageViewIfacePtr createMessageView() override;
	virtual SysUserListViewIfacePtr createSysUserListView() override;
	virtual LoginViewIfacePtr createLoginView() override;

};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_UI_FACTORY_HPP_ */
