# Basic functionality

GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)

CONFIGURE_FILE( "${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp" )

INCLUDE_DIRECTORIES(..)

ADD_LIBRARY(trihlavApi SHARED trihlavApi.cpp trihlavWrongConfigValue.cpp 
	trihlavYubikoOtpKeyConfig.cpp
		trihlavWrongConfigValue.cpp trihlavKeyManager.cpp trihlavVersion.cpp 
		trihlavYubikoOtpKeyPresenter.cpp
		trihlavFailedCreateConfigDir.cpp trihlavCannotWriteConfigDir.cpp
		trihlavLog.cpp trihlavIPresenter.cpp trihlavMainPanelPresenter.cpp
		trihlavCannotWriteConfigDir.cpp )

INSTALL(TARGETS trihlavApi LIBRARY DESTINATION lib)
