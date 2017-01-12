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
	virtual ~FactoryIface();
	virtual MainPanelViewIface* createMainPanelView()=0;
	virtual KeyListPresenterIface* createKeyListPresenter();
	virtual KeyListViewIface* createKeyListView()=0;
	virtual PswdChckPresenterIface* createPswdChckPresenter();
	virtual PswdChckViewIface* createPswdChckView() =0;
	virtual YubikoOtpKeyViewIface* createYubikoOtpKeyView() =0;
	virtual MessageViewIface* createMessageView() =0;
	virtual const KeyManager& getKeyManager() const;
	virtual KeyManager& getKeyManager();

	/// @brief OS System interface singleton
	virtual OsIface& getOsIface();

	/// @brief Global settings.
	virtual Settings& getSettings();

	/// @brief Select a operating system user
	virtual SysUserListViewIfacePtr createSysUserListView() =0;
private:
	std::unique_ptr<OsIface> itsOsIface;
};

}  // namespace trihlav

#endif /* TRIHLAV_FACTORY_IFACE_HPP_ */
