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

class ISpinBox;
class IStrEdit;
class IButton;

class IYubikoOtpKeyView {
public:
    typedef ::boost::signals2::signal<void(const bool)> AcceptedSignal ;

    AcceptedSignal& getAcceptedSignal() { return itsAcceptedSignal; }
    const AcceptedSignal& getAcceptedSignal() const { return itsAcceptedSignal; }

	virtual const IStrEdit& getEdtPublicId() const = 0;
	virtual IStrEdit& getEdtPublicId() = 0;

	virtual IStrEdit& getEdtDescription() = 0;
	virtual const IStrEdit& getEdtDescription() const = 0;

	virtual ISpinBox& getSbxPublicIdLen() = 0;
	virtual const ISpinBox& getSbxPublicIdLen() const = 0;

	virtual const IStrEdit& getEdtPrivateId() const = 0;
	virtual IStrEdit& getEdtPrivateId() = 0;

	virtual const IStrEdit& getEdtSecretKey() const = 0;
	virtual IStrEdit& getEdtSecretKey() = 0;

	virtual const IButton&  getBtnGenPublicId() const = 0;
	virtual IButton&  getBtnGenPublicId() = 0;

	virtual const IButton&  getBtnGenPrivateId() const = 0;
	virtual IButton&  getBtnGenPrivateId() = 0;

	virtual const IButton&  getBtnGenSecretKey() const = 0;
	virtual IButton&  getBtnGenSecretKey() = 0;

	virtual const IButton&  getBtnCancel() const = 0;
	virtual IButton&  getBtnCancel() = 0;

	virtual const IButton&  getBtnSave() const = 0;
	virtual IButton&  getBtnSave() = 0;

	virtual void show() = 0;

	virtual ~IYubikoOtpKeyView(){}
private:
    AcceptedSignal itsAcceptedSignal;
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_I_YUBIKO_OTP_KEY_VIEW_HPP_ */
