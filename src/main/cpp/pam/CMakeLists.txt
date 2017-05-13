# Basic functionality

INCLUDE_DIRECTORIES(.. ${PAM_INCLUDE_DIR})

ADD_LIBRARY(pam_trihlav SHARED trihlavPam.cpp trihlavSslClient.cpp 
    trihlavPam.cpp)

SET_TARGET_PROPERTIES(pam_trihlav PROPERTIES PREFIX "")

add_executable(trihlavSslClient trihlavSslClient.cpp trihlavSslClientTester.cpp 
    trihlavPam.cpp)
target_link_libraries(trihlavSslClient
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    ${PAM_LIBRARY}
)

# Ubuntu hardcoded - needs to be detected
SET(PAM_MODULES_DIR /lib/x86_64-linux-gnu/security )

INSTALL(TARGETS pam_trihlav LIBRARY DESTINATION ${PAM_MODULES_DIR})
