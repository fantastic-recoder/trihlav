# Basic test

set(TRIHLAV_TEST_INCLUDES ../../main/cpp 
	"googletest/googletest/include"
    "googletest/googlemock/include"
)

include_directories( ${TRIHLAV_TEST_INCLUDES} )

message(STATUS "Test include directories:${TRIHLAV_TEST_INCLUDES}.")

set(COMMON_INCLUDES trihlavMockButton.hpp trihlavMockSpinBox.hpp trihlavMockEditIface.hpp
		trihlavMockStrEdit.hpp trihlavMockStrEdit.cpp trihlavMockMessageView.hpp)

set(TRIHLAV_TEST_LIBS gtest gmock)

add_executable(trihlavTestApi trihlavTestApi.cpp ${COMMON_INCLUDES})

add_test(NAME trihlavTestApi COMMAND trihlavTestApi)

target_link_libraries(trihlavTestApi
        ${YUBIKEY_LIB}
        trihlavApi
        ${CMAKE_THREAD_LIBS_INIT}
        ${TRIHLAV_TEST_LIBS}
        ${Boost_LIBRARIES}
        ${PAM_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

add_executable(trihlavTestYubikoOtpKey trihlavTestYubikoOtpKey.cpp
        trihlavMockFactory.cpp trihlavMockKeyListView.cpp trihlavMockOs.cpp
        trihlavMockYubikoOtpKeyView.cpp trihlavMockPswdCheckView.cpp
        trihlavMockDialogView.cpp trihlavMockLoginView.cpp trihlavMockLabel.cpp ${COMMON_INCLUDES} trihlavTestCommonUtils.cpp trihlavTestCommonUtils.hpp)

add_test(NAME trihlavTestYubikoOtpKey COMMAND trihlavTestYubikoOtpKey)

target_link_libraries(trihlavTestYubikoOtpKey
        trihlavApi
        ${CMAKE_THREAD_LIBS_INIT}
        ${TRIHLAV_TEST_LIBS}
        ${YUBIKEY_LIB}
        ${Boost_LIBRARIES}
        ${PAM_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

add_executable(trihlavTestKeyListPresenter trihlavTestKeyListPresenter.cpp
        trihlavMockFactory.cpp trihlavMockKeyListView.cpp trihlavMockOs.cpp
        trihlavMockYubikoOtpKeyView.cpp trihlavMockPswdCheckView.cpp
        trihlavMockDialogView.cpp trihlavMockLoginView.cpp trihlavMockLabel.cpp ${COMMON_INCLUDES})

add_test(NAME trihlavTestKeyListPresenter COMMAND trihlavTestKeyListPresenter)

target_link_libraries(trihlavTestKeyListPresenter
        trihlavApi
        ${CMAKE_THREAD_LIBS_INIT}
        ${TRIHLAV_TEST_LIBS}
        ${YUBIKEY_LIB}
        ${Boost_LIBRARIES}
        ${PAM_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

add_executable(trihlavTestPswdChckPresenter trihlavTestPswdChckPresenter.cpp
        trihlavMockFactory.cpp trihlavMockKeyListView.cpp trihlavMockOs.cpp
        trihlavMockYubikoOtpKeyView.cpp trihlavMockPswdCheckView.cpp
		trihlavMockDialogView.cpp trihlavMockLoginView.cpp trihlavMockLabel.cpp ${COMMON_INCLUDES} trihlavTestCommonUtils.cpp trihlavTestCommonUtils.hpp trihlavMockStrEdit.cpp)

add_test(NAME trihlavTestPswdChckPresenter COMMAND trihlavTestPswdChckPresenter)

target_link_libraries(trihlavTestPswdChckPresenter
        trihlavApi
        ${CMAKE_THREAD_LIBS_INIT}
        ${TRIHLAV_TEST_LIBS}
        ${YUBIKEY_LIB}
        ${Boost_LIBRARIES}
        ${PAM_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

add_executable(trihlavTestOsIface trihlavTestOsIface.cpp ${COMMON_INCLUDES})

add_test(NAME trihlavTestOsIface COMMAND trihlavTestOsIface)

target_link_libraries(trihlavTestOsIface
        trihlavApi
        ${CMAKE_THREAD_LIBS_INIT}
        ${TRIHLAV_TEST_LIBS}
        ${YUBIKEY_LIB}
        ${Boost_LIBRARIES}
        ${PAM_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

add_executable(pretty_example pretty_example.cc)

target_link_libraries(pretty_example
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES}
        )

add_executable(trihlavPamTester trihlavPamTester.cpp)
target_link_libraries(trihlavPamTester
        trihlavApi
        ${YUBIKEY_LIB}
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES}
        ${PAM_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

add_executable(trihlavTestLoginPresenter trihlavTestLoginPresenter.cpp
        trihlavMockFactory.cpp trihlavMockKeyListView.cpp trihlavMockOs.cpp
        trihlavMockYubikoOtpKeyView.cpp trihlavMockPswdCheckView.cpp
        trihlavMockDialogView.cpp trihlavMockLoginView.cpp trihlavMockLabel.cpp
        ${COMMON_INCLUDES})

target_link_libraries(trihlavTestLoginPresenter
        trihlavApi
        ${CMAKE_THREAD_LIBS_INIT}
        ${TRIHLAV_TEST_LIBS}
        ${YUBIKEY_LIB}
        ${Boost_LIBRARIES}
        ${PAM_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

add_test(NAME trihlavTestLoginPresenter COMMAND trihlavTestLoginPresenter)


add_executable(trihlavTestTupleList trihlavTestTupleList.cpp ${COMMON_INCLUDES})

add_test(NAME trihlavTestTupleList COMMAND trihlavTestTupleList)

target_link_libraries(trihlavTestTupleList
        trihlavApi
        ${CMAKE_THREAD_LIBS_INIT}
        ${TRIHLAV_TEST_LIBS}
        ${YUBIKEY_LIB}
        ${Boost_LIBRARIES}
        ${PAM_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

