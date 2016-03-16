#ifndef TRIHLAV_LOG_HPP_
#define TRIHLAV_LOG_HPP_

#include <yubikey.h>

/**
 * Miscelanous logging related functionality is declared here.
 */
namespace trihlav {
	/// Initialize logging library.
	void initLog();
	void logDebug_token(const yubikey_token_st& pToken);

}

#endif // TRIHLAV_LOG_HPP_
