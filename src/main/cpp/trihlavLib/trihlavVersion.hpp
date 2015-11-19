/*
 * trihlavVersion.hpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#ifndef TRIHLAVVERSION_HPP_
#define TRIHLAVVERSION_HPP_

#include <boost/filesystem.hpp>

namespace trihlav {

class Version {
public:
	Version( const boost::filesystem::path& ){}
	virtual ~Version(){}
	static const std::string getVersion();
};

} /* namespace trihlavApi */

#endif /* TRIHLAVVERSION_HPP_ */

