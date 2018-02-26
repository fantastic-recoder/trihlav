# Main server
INCLUDE_DIRECTORIES(${Wt_INCLUDE_DIR} ..)

add_executable(trihlavsrv main.cpp trihlavApp.cpp trihlavApp.hpp trihlavWtUiFactory.cpp
        trihlavWtMainPanelView.cpp trihlavWtPswdChckView.cpp
        trihlavWtKeyListView.cpp trihlavWtKeyListView.hpp
        trihlavWtMessageView.cpp trihlavWtPushButton.cpp
        trihlavWtSpinBox.cpp trihlavWtYubikoOtpKeyView.cpp trihlavWtStrEdit.cpp
        trihlavWtSysUserListIView.cpp trihlavWtDialogView.cpp trihlavWtDialogView.hpp
        trihlavWtAuthResource.cpp trihlavWtAuthResource.hpp trihlavWtLoginView.cpp
        trihlavWtLoginView.hpp trihlavWtLabel.cpp trihlavWtLabel.hpp trihlavWtListModel.hpp
        trihlavWtViewIface.hpp)

TARGET_LINK_LIBRARIES(trihlavsrv
        trihlavApi
        #${Wt_DEBUG_LIBRARY}
        ${Wt_LIBRARY}
        #${Wt_HTTP_DEBUG_LIBRARY}
        ${Wt_HTTP_LIBRARY}
        ${YUBIKEY_LIB}
        #${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES}
        ${PAM_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

INSTALL(TARGETS trihlavsrv RUNTIME DESTINATION bin)
