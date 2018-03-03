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

#ifndef TRIHLAV_SPIN_BOX_IFACE_HPP_
#define TRIHLAV_SPIN_BOX_IFACE_HPP_

#include "trihlavEditIface.hpp"

namespace trihlav {

    class SpinBoxIface {
    public:
        SpinBoxIface() = default;

        SpinBoxIface(SpinBoxIface &) = delete;

        virtual const int getValue() const =0;

        virtual void setValue(const int &pVal)=0;

        virtual void setMin(int pMin)=0;

        virtual const int getMin() const =0;

        virtual void setMax(int pMax)=0;

        virtual const int getMax() const =0;

        virtual void setStep(int pStep)=0;

        virtual const int getStep() const =0;

        virtual ~SpinBoxIface();

    };

} /* namespace trihlav */

#endif /* TRIHLAV_SPIN_BOX_IFACE_HPP_ */
