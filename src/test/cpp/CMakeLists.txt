# Basic test

include_directories(../../main/cpp)

add_executable( trihlavApiTests trihlavApiTests.cpp )

add_test( NAME trihlavApiTests COMMAND trihlavApiTests )

target_link_libraries(trihlavApiTests
                      ${Boost_LIBRARIES}
                      ${YUBIKEY_LIB}
                      trihlavApi
                      ${CMAKE_THREAD_LIBS_INIT}
                      )
