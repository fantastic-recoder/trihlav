###############################################################################
#
cmake_minimum_required(VERSION 2.6)

project(trihlavsrv)

FIND_PACKAGE( Wt REQUIRED )

INCLUDE_DIRECTORIES( ${Wt_INCLUDE_DIR} )

add_executable(trihlavsrv main.cpp)

TARGET_LINK_LIBRARIES( trihlavsrv
    #${Wt_DEBUG_LIBRARY}        
    ${Wt_LIBRARY}
    #${Wt_HTTP_DEBUG_LIBRARY}   
    ${Wt_HTTP_LIBRARY}
    #${Wt_EXT_DEBUG_LIBRARY}   
    ${Wt_EXT_LIBRARY}
)

install(TARGETS trihlavsrv RUNTIME DESTINATION bin)
