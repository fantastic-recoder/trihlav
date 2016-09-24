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
#ifndef TRIHLAV_I_YUBIKO_OTP_KEY_VIEW_HPP_
#define TRIHLAV_I_YUBIKO_OTP_KEY_VIEW_HPP_

#include <boost/signals2.hpp>

namespace trihlav {

class SpinBoxIface;
class StrEditIface;
class ButtonIface;

class YubikoOtpKeyViewIface : private boost::noncopyable {
public:
    typedef ::boost::signals2::signal<void(const bool)> AcceptedSignal ;

    AcceptedSignal acceptedSig;

    virtual const StrEditIface& getEdtPublicId() const = 0;
	virtual StrEditIface& getEdtPublicId() = 0;

	virtual StrEditIface& getEdtDescription() = 0;
	virtual const StrEditIface& getEdtDescription() const = 0;

	virtual SpinBoxIface& getSbxPublicIdLen() = 0;
	virtual const SpinBoxIface& getSbxPublicIdLen() const = 0;

	virtual const StrEditIface& getEdtPrivateId() const = 0;
	virtual StrEditIface& getEdtPrivateId() = 0;

	virtual const StrEditIface& getEdtSysUser() const = 0;
	virtual StrEditIface& getEdtSysUser() = 0;

	virtual const StrEditIface& getEdtSecretKey() const = 0;
	virtual StrEditIface& getEdtSecretKey() = 0;

	virtual const ButtonIface&  getBtnGenPublicId() const = 0;
	virtual ButtonIface&  getBtnGenPublicId() = 0;

	virtual const ButtonIface&  getBtnGenPrivateId() const = 0;
	virtual ButtonIface&  getBtnGenPrivateId() = 0;

	virtual const ButtonIface&  getBtnSelectSysUser() const = 0;
	virtual ButtonIface&  getBtnSelectSysUser() = 0;

	virtual const ButtonIface&  getBtnGenSecretKey() const = 0;
	virtual ButtonIface&  getBtnGenSecretKey() = 0;

	virtual const ButtonIface&  getBtnCancel() const = 0;
	virtual ButtonIface&  getBtnCancel() = 0;

	virtual const ButtonIface&  getBtnSave() const = 0;
	virtual ButtonIface&  getBtnSave() = 0;

	virtual void show() = 0;

	virtual ~YubikoOtpKeyViewIface();
private:
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_I_YUBIKO_OTP_KEY_VIEW_HPP_ */
