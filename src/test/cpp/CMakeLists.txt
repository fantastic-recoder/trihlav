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

add_executable( trihlavYubikoOtpKeyTests trihlavYubikoOtpKeyTests.cpp trihlavGlobalFixture.cpp trihlavTestGetFactory.cpp)

add_test( NAME trihlavYubikoOtpKeyTests COMMAND trihlavYubikoOtpKeyTests )

target_link_libraries(trihlavYubikoOtpKeyTests
                      ${Boost_LIBRARIES}
                      ${YUBIKEY_LIB}
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      )

