/*
 * trihlavIEdit.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_I_EDIT_HPP_
#define TRIHLAV_I_EDIT_HPP_

#include <string>

#include "trihlavLib/trihlavICallback.hpp"
#include "trihlavLib/trihlavIWidget.hpp"

namespace trihlav {

template< class T>
class IEdit : virtual public IWidget {
public:
	virtual void setCallback(IValCallback<T>& pCallback) = 0;
	virtual const T& getValue() const = 0;
	virtual void setValue(const T& pVal) =0;
	virtual ~IEdit()=0;
};

typedef IEdit<std::string> IStrEdit;

} /* namespace trihlav */

#endif /* TRIHLAV_I_EDIT_HPP_ */
