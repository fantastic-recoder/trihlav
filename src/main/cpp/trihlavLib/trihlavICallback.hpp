/*
 * trihlavICallback.hpp
 *
 *  Created on: 26.11.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_ICALLBACK_HPP_
#define TRIHLAV_ICALLBACK_HPP_

namespace trihlav {

	class ICallback {
		virtual void callback()=0;
	};

	template <class T>
	class IValCallback {
		virtual void callback( const T& pVal)=0;
	};

} // end namespace trihlav

#endif /* TRIHLAV_ICALLBACK_HPP_ */
