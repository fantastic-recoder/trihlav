# Basic functionality

add_library(trihlavApi SHARED trihlavApi.cpp trihlavWrongConfigValue.cpp)

TARGET_LINK_LIBRARIES( yubiko )

install(TARGETS trihlavApi LIBRARY DESTINATION lib)
