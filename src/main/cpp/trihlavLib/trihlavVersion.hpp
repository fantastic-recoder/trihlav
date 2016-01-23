/*
 * trihlavVersion.hpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#ifndef TRIHLAV_VERSION_HPP_
#define TRIHLAV_VERSION_HPP_

#include <boost/filesystem.hpp>

namespace trihlav {

class Version {
public:
	Version( const boost::filesystem::path& ){}
	virtual ~Version(){}
	static const std::string getVersion();
};

} /* namespace trihlavApi */

#endif /* TRIHLAV_VERSION_HPP_ */

