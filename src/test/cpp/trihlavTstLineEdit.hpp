/*
 * trihlavTstLineEdit.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_TST_LINE_EDIT_HPP_
#define TRIHLAV_TST_LINE_EDIT_HPP_

#include <string>
#include <trihlavLib/trihlavILineEdit.hpp>

namespace trihlav {

/**
 * A dummy/test implementation of a virtual line editor UI element.
 */
class TstLineEdit: public ILineEdit {
	std::string itsVal;
public:
	TstLineEdit() {}
	TstLineEdit(const std::string& pInitVal ):itsVal(pInitVal) {}
	virtual ~TstLineEdit();
	virtual const std::string& getValue() const {return itsVal; }
	virtual void setValue(const std::string& pVal) {
		itsVal=pVal;
	}
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_TST_LINE_EDIT_HPP_ */
