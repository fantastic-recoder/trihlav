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

#include "trihlavLib/trihlavIYubikoOtpKeyPresenter.hpp"

namespace trihlav {

class IFactory;
class IYubikoOtpKeyView;
class YubikoOtpKeyConfig;
class IStrEdit;

/**
 * @brief Presents an @see YubikoOtpKeyConfig
 */
class YubikoOtpKeyPresenter: public IYubikoOtpKeyPresenter {
public:
    typedef std::unique_ptr<YubikoOtpKeyConfig> YubikoOtpKeyConfigPtr;

    YubikoOtpKeyPresenter(const IFactory& );

    virtual ~YubikoOtpKeyPresenter();

    /// @brief Add a new key and present it in its view.
    virtual void addKey();

    /// @brief delete current key being edited.
    virtual void deleteKey();

    virtual YubikoOtpKeyConfigPtr& getCurCfg() {
      return itsCurCfg;
    }

    virtual const YubikoOtpKeyConfigPtr& getCurCfg() const {
      return itsCurCfg;
    }

    /// @brief generate random private id
    virtual void generatePrivateId();
    /// @brief generate random public id
    virtual void generatePublicId();
    /// @brief generate random secret key
    virtual void generateSecretKey();
    /// @brief get the length of public id.
	int getPublicIdLen() const;

	/// @brief Accessor returns private id edit widget.
	IStrEdit& getEdtPrivateId();

	/// @brief Accessor returns private id edit widget.
	const IStrEdit& getEdtPrivateId() const;

	IYubikoOtpKeyView& getView();
	const IYubikoOtpKeyView& getView() const;

    /// @brief generate random hex encoded byte array
    static void generate(int pBytes, std::string& pTarget) ;

	/// @brief Accessor returns secret key edit widget.
	IStrEdit& getEdtSecretKey();

	/// @brief Const accessor returns secret key edit widget.
	const IStrEdit& getEdtSecretKey() const;

	/// @brief Accessor returns secret key edit widget.
	IStrEdit& getEdtPublicId();

	/// @brief Const accessor returns secret key edit widget.
	const IStrEdit& getEdtPublicId() const;

	/// @brief Public ID getter.
	const std::string getPublicId() const;

	/// @brief Private id from UI getter.
	const std::string getPrivateId() const;

	/// @brief Secret key getter.
	const std::string getSecretKey() const;

	/// @brief Description getter.
	const std::string getDescription() const;

private:
    IYubikoOtpKeyView* itsView;
    YubikoOtpKeyConfigPtr itsCurCfg;
    YubikoOtpKeyConfigPtr itsOldCfg;
    void accepted( bool pAccepted);
	void throwNoConfig();
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_YUBIKO_OPT_KEY_PRESENTER_HPP_ */
