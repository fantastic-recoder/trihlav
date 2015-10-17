# Basic functionality

CONFIGURE_FILE( "${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp" )

add_library(trihlavApi SHARED trihlavApi.cpp trihlavWrongConfigValue.cpp trihlavYubikoOtpKeyConfig.cpp 
	trihlavWrongConfigValue.cpp trihlavVersion.cpp)

install(TARGETS trihlavApi LIBRARY DESTINATION lib)
