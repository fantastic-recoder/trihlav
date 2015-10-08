# Basic functionality

add_library(trihlavApi SHARED trihlavApi.cpp trihlavWrongConfigValue.cpp trihlavYubikoOtpKeyConfig.cpp 
	trihlavWrongConfigValue.cpp)

install(TARGETS trihlavApi LIBRARY DESTINATION lib)
