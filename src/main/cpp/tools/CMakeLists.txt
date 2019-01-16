# Basic functionality

INCLUDE_DIRECTORIES(.. ${PAM_INCLUDE_DIR})

ADD_EXECUTABLE(trihlavCmd trihlavCmdMain.cpp)

TARGET_LINK_LIBRARIES(trihlavCmd
        trihlavApi
        ${Boost_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${YUBIKEY_LIB}
        ${PAM_LIBRARIES}
        )

