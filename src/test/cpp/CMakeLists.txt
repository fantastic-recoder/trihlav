# Basic test

include_directories(
	../../main/cpp  
	${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

add_executable( trihlavTestApi trihlavTestApi.cpp )

add_test( NAME trihlavTestApi COMMAND trihlavTestApi )

target_link_libraries(trihlavTestApi
                      ${Boost_LIBRARIES}
                      ${YUBIKEY_LIB}
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      libgtest
    				  libgmock
                      )

add_executable( trihlavTestYubikoOtpKey trihlavTestYubikoOtpKey.cpp 
trihlavMockFactory.cpp trihlavMockKeyListView.cpp
trihlavMockYubikoOtpKeyView.cpp trihlavMockYubikoOtpKeyPresenter.cpp)

add_test( NAME trihlavTestYubikoOtpKey COMMAND trihlavTestYubikoOtpKey )

target_link_libraries(trihlavTestYubikoOtpKey
                      	${Boost_LIBRARIES}
                      	${YUBIKEY_LIB}
                      	trihlavApi
                      	${CMAKE_THREAD_LIBS_INIT}
                        libgtest
    					libgmock
                      )

add_executable( trihlavTestKeyListPresenter trihlavTestKeyListPresenter.cpp 
	trihlavMockFactory.cpp trihlavMockKeyListView.cpp
	trihlavMockYubikoOtpKeyView.cpp trihlavMockYubikoOtpKeyPresenter.cpp)

add_test( NAME trihlavTestKeyListPresenter COMMAND trihlavTestKeyListPresenter )

target_link_libraries(trihlavTestKeyListPresenter
                      ${Boost_LIBRARIES}
                      ${YUBIKEY_LIB}
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      libgtest
    				  libgmock
                      )
