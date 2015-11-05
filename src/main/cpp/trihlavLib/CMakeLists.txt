# Basic functionality

GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)

CONFIGURE_FILE( "${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp" )

ADD_LIBRARY(trihlavApi SHARED trihlavApi.cpp trihlavWrongConfigValue.cpp trihlavYubikoOtpKeyConfig.cpp
		trihlavWrongConfigValue.cpp trihlavKeyManager.cpp trihlavVersion.cpp trihlavFailedCreateConfigDir.cpp trihlavFailedCreateConfigDir.hpp)

INSTALL(TARGETS trihlavApi LIBRARY DESTINATION lib)
