/*
 * trihlavIButton.hpp
 *
 *  Created on: 26.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_IBUTTON_HPP_
#define TRIHLAV_IBUTTON_HPP_

#include <trihlavLib/trihlavICallback.hpp>

namespace trihlav {
	class IButton {
		virtual void setCallback( ICallback& pCallback)=0;
		virtual ~IButton()=0;
	};
}

#endif /* TRIHLAV_IBUTTON_HPP_ */
