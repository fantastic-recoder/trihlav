/*
 * trihlavILineEdit.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_I_LINE_EDIT_HPP_
#define TRIHLAV_I_LINE_EDIT_HPP_

#include <string>

namespace trihlav {

class ILineEdit {
public:
	virtual const std::string& getValue() const = 0;
	virtual void setValue(const std::string& pVal) =0;
	virtual ~ILineEdit()=0;
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_I_LINE_EDIT_HPP_ */
