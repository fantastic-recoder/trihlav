/*
 * trihlavIEdit.hpp
 *
 *  Created on: 17.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_I_EDIT_HPP_
#define TRIHLAV_I_EDIT_HPP_

#include <string>
#include <boost/utility.hpp>

#include "trihlavLib/trihlavICallback.hpp"

namespace trihlav {

/**
 * Interface to a UI widget, which can edit, set and get a value.
 */
template< typename T>
class IEdit : virtual public boost::noncopyable {
public:
	/**
	 * @return The edited value.
	 */
	virtual const T getValue() const = 0;

	/**
	 * @param pVal set the value, which can be edited.
	 */
	virtual void setValue(const T& pVal) =0;

	/// Just ensure virtual destructor.
	virtual ~IEdit(){}
};

struct IStrEdit: virtual public IEdit<std::string>{};

} /* namespace trihlav */

#endif /* TRIHLAV_I_EDIT_HPP_ */
