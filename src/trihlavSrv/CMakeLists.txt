FIND_PACKAGE( Wt REQUIRED )

INCLUDE_DIRECTORIES( ${Wt_INCLUDE_DIR} )

add_executable(trihlavsrv main.cpp trihlavApp.cpp)

TARGET_LINK_LIBRARIES( trihlavsrv
    #${Wt_DEBUG_LIBRARY}        
    ${Wt_LIBRARY}
    #${Wt_HTTP_DEBUG_LIBRARY}   
    ${Wt_HTTP_LIBRARY}
)

install(TARGETS trihlavsrv RUNTIME DESTINATION bin)
