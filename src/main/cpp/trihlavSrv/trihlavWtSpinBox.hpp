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
#ifndef TRIHLAV_WT_SPIN_BOX_HPP_
#define TRIHLAV_WT_SPIN_BOX_HPP_

#include <Wt/WSpinBox.h>

#include "../trihlavLib/trihlavSpinBoxIface.hpp"

namespace trihlav {

    class WtSpinBox : virtual public SpinBoxIface, virtual public Wt::WSpinBox {
    public:
        virtual ~WtSpinBox();

        WtSpinBox();

        virtual void setMin(const int pMin) {
            Wt::WSpinBox::setMinimum(pMin);
        }

        virtual const int getMin() const {
            return minimum();
        }

        virtual void setMax(const int pMax) {
            Wt::WSpinBox::setMaximum(pMax);
        }

        virtual const int getMax() const {
            return maximum();
        }

        virtual void setStep(const int pStep) {
            Wt::WSpinBox::setSingleStep(pStep);
        }

        virtual const int getStep() const {
            return singleStep();
        }

        virtual const int getValue() const {
            return value();
        }

        virtual void setValue(const int &pVal) {
            Wt::WSpinBox::setValue(pVal);
        }
    };

} /* namespace trihlav */

#endif /* TRIHLAV_WT_SPIN_BOX_HPP_ */
