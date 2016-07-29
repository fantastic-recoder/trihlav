# Basic test

include_directories(
	../../main/cpp  
	${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

add_executable( trihlavTestApi trihlavTestApi.cpp )

add_test( NAME trihlavTestApi COMMAND trihlavTestApi )

target_link_libraries(trihlavTestApi
                      ${YUBIKEY_LIB}
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      libgtest
    				  libgmock
                      ${Boost_LIBRARIES}
                      ${PAM_LIBRARIES}
                      )

add_executable( trihlavTestYubikoOtpKey trihlavTestYubikoOtpKey.cpp 
trihlavMockFactory.cpp trihlavMockKeyListView.cpp
trihlavMockYubikoOtpKeyView.cpp trihlavMockPswdCheckView.cpp)

add_test( NAME trihlavTestYubikoOtpKey COMMAND trihlavTestYubikoOtpKey )

target_link_libraries(trihlavTestYubikoOtpKey
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      libgtest
                      libgmock
                      ${YUBIKEY_LIB}
                      ${Boost_LIBRARIES}
                      ${PAM_LIBRARIES}
                      )

add_executable( trihlavTestKeyListPresenter trihlavTestKeyListPresenter.cpp 
	trihlavMockFactory.cpp trihlavMockKeyListView.cpp
	trihlavMockYubikoOtpKeyView.cpp trihlavMockPswdCheckView.cpp)

add_test( NAME trihlavTestKeyListPresenter COMMAND trihlavTestKeyListPresenter )

target_link_libraries(trihlavTestKeyListPresenter
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      libgtest
    				  libgmock
                      ${YUBIKEY_LIB}
                      ${Boost_LIBRARIES}
                      ${PAM_LIBRARIES}
                      )

add_executable( trihlavTestPswdChckPresenter trihlavTestPswdChckPresenter.cpp 
	trihlavMockFactory.cpp trihlavMockKeyListView.cpp
	trihlavMockYubikoOtpKeyView.cpp trihlavMockPswdCheckView.cpp
	)

add_test( NAME trihlavTestPswdChckPresenter COMMAND trihlavTestPswdChckPresenter )

target_link_libraries(trihlavTestPswdChckPresenter
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      libgtest
    				  libgmock
                      ${YUBIKEY_LIB}
                      ${Boost_LIBRARIES}
                      ${PAM_LIBRARIES}
                      )

add_executable( trihlavTestOsIface trihlavTestOsIface.cpp )

add_test( NAME trihlavTestOsIface COMMAND trihlavTestOsIface )

target_link_libraries(trihlavTestOsIface
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      libgtest
    				  libgmock
                      ${YUBIKEY_LIB}
                      ${Boost_LIBRARIES}
                      ${PAM_LIBRARIES}
                      )
                      
add_executable( pretty_example pretty_example.cc )

target_link_libraries(pretty_example
                      ${CMAKE_THREAD_LIBS_INIT}
                      ${Boost_LIBRARIES}
                      )
