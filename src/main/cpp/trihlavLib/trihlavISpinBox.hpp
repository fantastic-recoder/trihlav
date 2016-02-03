/*
 * trihlavISpinBox.hpp
 *
 *  Created on: 03.02.2016
 *      Author: grobap
 */

#ifndef TRIHLAVISPINBOX_HPP_
#define TRIHLAVISPINBOX_HPP_

#include "trihlavLib/trihlavIEdit.hpp"

namespace trihlav {

class ISpinBox: public IEdit<int> {
public:
	virtual void setMin(const int pMin)=0;
	virtual const int getMin() const =0;
	virtual void setMax(const int pMax)=0;
	virtual const int getMax() const =0;
	virtual void setStep(const int pStep)=0;
	virtual const int getStep() const =0;
	virtual ~ISpinBox() {
	}
};

} /* namespace trihlav */

#endif /* TRIHLAVISPINBOX_HPP_ */
