# Basic test

include_directories(../../main/cpp)

add_executable( trihlavApiTests trihlavApiTests.cpp trihlavGlobalFixture.cpp trihlavTestGetFactory.cpp)

add_test( NAME trihlavApiTests COMMAND trihlavApiTests )

target_link_libraries(trihlavApiTests
                      ${Boost_LIBRARIES}
                      ${YUBIKEY_LIB}
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      )

add_executable( trihlavTestYubikoOtpKey trihlavTestYubikoOtpKey.cpp trihlavGlobalFixture.cpp trihlavTestGetFactory.cpp)

add_test( NAME trihlavTestYubikoOtpKey COMMAND trihlavTestYubikoOtpKey )

target_link_libraries(trihlavTestYubikoOtpKey
                      ${Boost_LIBRARIES}
                      ${YUBIKEY_LIB}
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      )

add_executable( trihlavTestKeyListPresenter trihlavTestKeyListPresenter.cpp trihlavGlobalFixture.cpp)

add_test( NAME trihlavTestKeyListPresenter COMMAND trihlavTestKeyListPresenter )

target_link_libraries(trihlavTestKeyListPresenter
                      ${Boost_LIBRARIES}
                      ${YUBIKEY_LIB}
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      )

