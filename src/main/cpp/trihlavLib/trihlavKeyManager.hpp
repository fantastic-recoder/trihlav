/*
 * trihlavKeyManager.hpp
 *
 *  Created on: 17.10.2015
 *      Author: grobap
 */

#ifndef TRIHLAVKEYMANAGER_HPP_
#define TRIHLAVKEYMANAGER_HPP_

#include <boost/filesystem.hpp>

namespace trihlavApi {

/**
 * Manage key operations, fe. their persistence.
 */
class KeyManager {
	bool itsInitializedFlag;
	boost::filesystem::path itsConfigDir;
public:
	/// Lazy initialization constructor.
	KeyManager(const boost::filesystem::path& pDir);

	virtual ~KeyManager();

	const boost::filesystem::path& getConfigDir();

	/**
	 * Are all internal resources ready.
	 */
	const bool isInitialized() const {
		return itsInitializedFlag;
	}
};

} /* namespace trihlav */

#endif /* TRIHLAVKEYMANAGER_HPP_ */
