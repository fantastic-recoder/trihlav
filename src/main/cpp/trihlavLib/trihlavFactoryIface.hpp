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

#ifndef TRIHLAV_FACTORY_IFACE_HPP_
#define TRIHLAV_FACTORY_IFACE_HPP_

#include <memory>

#include "trihlavLib/trihlavGlobals.hpp"

namespace trihlav {

class MainPanelViewIface;
class KeyListPresenterIface;
class KeyListViewIface;
class PswdChckPresenterIface;
class PswdChckViewIface;
class YubikoOtpKeyViewIface;
class YubikoOtpKeyPresenterIface;
class MessageViewIface;
class OsIface;
class SysUserListViewIface;
class Settings;
class KeyManager;

using SysUserListViewIfacePtr = std::shared_ptr<SysUserListViewIface>;

class FactoryIface {
public:

	FactoryIface();

	virtual ~FactoryIface();
	virtual MainPanelViewIfacePtr createMainPanelView()=0;
	virtual KeyListPresenterIfacePtr createKeyListPresenter();
	virtual KeyListViewIfacePtr createKeyListView()=0;
	virtual PswdChckPresenterIfacePtr createPswdChckPresenter();
	virtual PswdChckViewIfacePtr createPswdChckView() =0;
	virtual YubikoOtpKeyViewIfacePtr createYubikoOtpKeyView() =0;
	virtual MessageViewIfacePtr createMessageView() =0;
	virtual const KeyManager& getKeyManager() const;
	virtual KeyManager& getKeyManager();

	/// @brief OS System interface singleton
	virtual OsIface& getOsIface();

	/// @brief Global settings.
	Settings &getSettings();

	/// @brief Select a operating system user
	virtual SysUserListViewIfacePtr createSysUserListView() =0;

	/// @brief Login in the operating system UI.
	virtual LoginViewIfacePtr createLoginView()=0;
private:
	std::unique_ptr<OsIface> m_OsIface;
	std::unique_ptr<KeyManager> m_KeyManager;
};

}  // namespace trihlav

#endif /* TRIHLAV_FACTORY_IFACE_HPP_ */
