/*
 * trihlavGlobalFixture.cpp
 *
 *  Created on: 29.11.2015
 *      Author: grobap
 */

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "trihlavGlobalFixture.hpp"
#include "trihlavLib/trihlavLog.hpp"


namespace trihlav {

GlobalFixture::GlobalFixture() {
	BOOST_LOG_NAMED_SCOPE("GlobalFixture::GlobalFixture");
	initLog();
}

GlobalFixture::~GlobalFixture() {
	BOOST_LOG_NAMED_SCOPE("GlobalFixture::~GlobalFixture");
}

} /* namespace trihlav */
