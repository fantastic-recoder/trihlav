/*
 * trihlavVersion.hpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#ifndef TRIHLAVVERSION_HPP_
#define TRIHLAVVERSION_HPP_

namespace trihlav {

class Version {
public:
	Version(){}
	virtual ~Version(){}
	std::string getVersion() const;
};

} /* namespace trihlav */

#endif /* TRIHLAVVERSION_HPP_ */

