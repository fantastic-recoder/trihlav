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
#ifndef TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_
#define TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_

#include <memory>
#include <boost/signals2.hpp>

#include "trihlavLib/trihlavGlobals.hpp"
#include "trihlavLib/trihlavPresenterBase.hpp"

namespace trihlav {

class FactoryIface;
class YubikoOtpKeyConfig;
class StrEditIface;
class SysUserListPresenter;

using signal_t=boost::signals2::signal<void()>;

/**
 * @brief Presents an @see YubikoOtpKeyConfig
 */
class YubikoOtpKeyPresenter: virtual public PresenterBase {
public:

	enum EMode {None,Edit,Add,Delete};

    YubikoOtpKeyPresenter(FactoryIface&);

    virtual ~YubikoOtpKeyPresenter();

    /// @brief Add a new key and present it in its view.
    virtual void addKey();

    /// @brief delete current key being edited.
    virtual void deleteKey();

    void deleteKey(const YubikoOtpKeyConfig& pKeyCfg );

    void editKey(const YubikoOtpKeyConfig& pKeyCfg );

    virtual YubikoOtpKeyConfig& getCurCfg();

    /// @brief generate random private id
    virtual void generatePrivateId();

    /// @brief generate random public id
    virtual void generatePublicId();

    /// @brief generate random secret key
    virtual void generateSecretKey();

    /// @brief get the length of public id.
	int getPublicIdLen();

	/// @brief Accessor returns private id edit widget.
	StrEditIface& getEdtPrivateId();

	YubikoOtpKeyViewIface& getView();

    /// @brief generate random hex encoded byte array
    static void generate(int pBytes, std::string& pTarget) ;

    /// @brief generate random modhex encoded byte array
    static void generateModhex(int pBytes, std::string& pTarget) ;

	/// @brief Accessor returns secret key edit widget.
	StrEditIface& getEdtSecretKey();

	/// @brief Accessor returns secret key edit widget.
	StrEditIface& getEdtPublicId();

	/// @brief Public ID getter.
	std::string getPublicId();

	/// @brief Private id from UI getter.
	std::string getPrivateId();

	/// @brief Secret key getter.
	std::string getSecretKey();

	/// @brief Description getter.
	std::string getDescription();

	void showCurrentConfig();

	MessageViewIface& getMessageView();

	SysUserListPresenter& getSysUserListPresenter();

	void selectSystemUser();

	void systemUserSelected();

	signal_t saved;
private:
	EMode itsMode=None;
    YubikoOtpKeyViewIfacePtr itsView;
    YubikoOtpKeyConfig* itsCurCfg;
    void accepted( bool pAccepted);
	void throwNoConfig();
	void initUi();
	std::unique_ptr<MessageViewIface> itsMessageView;
	std::unique_ptr<SysUserListPresenter> itsSysUserListPresenter;
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_ */
