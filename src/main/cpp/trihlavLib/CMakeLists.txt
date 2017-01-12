# Basic functionality

GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)

CONFIGURE_FILE( "${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp" )

INCLUDE_DIRECTORIES(.. ${PAM_INCLUDE_DIR})

ADD_LIBRARY(trihlavApi SHARED trihlavApi.cpp trihlavWrongConfigValue.cpp 
	trihlavYubikoOtpKeyConfig.cpp
	trihlavWrongConfigValue.cpp trihlavKeyManager.cpp trihlavVersion.cpp 
	trihlavYubikoOtpKeyPresenter.cpp
	trihlavFailedCreateConfigDir.cpp trihlavCannotWriteConfigDir.cpp
	trihlavLog.cpp trihlavPresenterBase.cpp trihlavMainPanelPresenter.cpp
	trihlavCannotWriteConfigDir.cpp trihlavFactoryIface.cpp 
	trihlavPswdChckPresenter.cpp trihlavKeyListPresenter.cpp trihlavKeyListViewIface.cpp
	trihlavYubikoOtpKeyViewIface.cpp trihlavCannotCastImplementation.cpp
    trihlavMessageViewIface.cpp trihlavEmptyPublicId.cpp trihlavWidgetIface.cpp
    trihlavOsIface.cpp trihlavSysUserListPresenter.cpp trihlavDialogViewIface.cpp 
    trihlavLogApi.hpp trihlavSettings.cpp trihlavSettings.hpp  
    trihlavLoginPresenter.cpp  trihlavLoginPresenter.hpp trihlavLabelIface.cpp 
    trihlavLabelIface.hpp)

INSTALL(TARGETS trihlavApi LIBRARY DESTINATION lib)
