# Main server
INCLUDE_DIRECTORIES( ${Wt_INCLUDE_DIR} ..)

add_executable(trihlavsrv main.cpp trihlavApp.cpp trihlavWtUiFactory.cpp 
	trihlavWtMainPanelView.cpp trihlavWtPswdChckView.cpp 
	trihlavWtKeyListView.cpp trihlavWtMessageView.cpp trihlavWtPushButton.cpp 
	trihlavWtSpinBox.cpp trihlavWtYubikoOtpKeyView.cpp trihlavWtStrEdit.cpp )

TARGET_LINK_LIBRARIES( trihlavsrv
	trihlavApi
    #${Wt_DEBUG_LIBRARY}        
    ${Wt_LIBRARY}
    #${Wt_HTTP_DEBUG_LIBRARY}   
    ${Wt_HTTP_LIBRARY}
    ${YUBIKEY_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
)

INSTALL(TARGETS trihlavsrv RUNTIME DESTINATION bin)
