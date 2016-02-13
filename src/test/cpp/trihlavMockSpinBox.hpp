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
#ifndef TRIHLAV_MOCK_SPIN_BOX_HPP_
#define TRIHLAV_MOCK_SPIN_BOX_HPP_

#include "trihlavLib/trihlavISpinBox.hpp"
#include "trihlavMockEditI.hpp"

namespace trihlav {

struct MockSpinBox: virtual public ISpinBox {
	int itsVal;
	int itsMin;
	int itsMax;
	int itsStep;

	/**
	 * Set some unlikely initialization values like min = -1, max = -1 und
	 * step = 0.
	 */
	MockSpinBox():itsVal(0), itsMin(-1),itsMax(-1),itsStep(0) {
	}

	virtual const int getValue() const {
		return itsVal;
	}

	virtual void setValue(const int& pVal) {
		itsVal=pVal;
	}

	virtual void setMin(const int pMin) {
		itsMin = pMin;
	}

	virtual const int getMin() const {
		return itsMin;
	}

	virtual void setMax(const int pMax) {
		itsMax = pMax;
	}

	virtual const int getMax() const {
		return itsMax;
	}

	virtual void setStep(const int pStep) {
		itsStep = pStep;
	}

	virtual const int getStep() const {
		return itsStep;
	}

};



}  // namespace trihlav



#endif /* TRIHLAV_MOCK_SPIN_BOX_HPP_ */
