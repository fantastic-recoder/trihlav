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

#include <trihlavLib/trihlavIEdit.hpp>
#include <trihlavLib/trihlavIButton.hpp>

namespace trihlav {

class IYubikoOtpKeyView {
public:
    typedef ::boost::signals2::signal<void(const bool)> AcceptedSignal ;

    AcceptedSignal& getAcceptedSignal() { return itsAcceptedSignal; }
    const AcceptedSignal& getAcceptedSignal() const { return itsAcceptedSignal; }

	virtual const IStrEdit& getPublicId() const=0;
	virtual IStrEdit& getPublicId()=0;

	virtual IStrEdit& getPublicIdLen()=0;
	virtual const IStrEdit& getPublicIdLen() const=0;

	virtual const IStrEdit& getPrivateId() const=0;
	virtual IStrEdit& getPrivateId()=0;

	virtual const IStrEdit& getSecretKey() const=0;
	virtual IStrEdit& getSecretKey()=0;

	virtual const IButton&  getGenPublicIdentityBtn() const =0;
	virtual IButton&  getGenPublicIdentityBtn() =0;

	virtual const IButton&  getGenPrivateIdentityBtn() const =0;
	virtual IButton&  getGenPrivateIdentityBtn() =0;

	virtual const IButton&  getGenSecretKeyBtn() const =0;
	virtual IButton&  getGenSecretKeyBtn() =0;

	virtual const IButton&  getCancelBtn() const =0;
	virtual IButton&  getCancelBtn() =0;

	virtual const IButton&  getSaveBtn() const =0;
	virtual IButton&  getSaveBtn() =0;

	virtual void show() =0;

	virtual ~IYubikoOtpKeyView(){}
private:
    AcceptedSignal itsAcceptedSignal;
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_I_YUBIKO_OTP_KEY_VIEW_HPP_ */
