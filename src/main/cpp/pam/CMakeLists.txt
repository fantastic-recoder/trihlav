# Basic functionality

INCLUDE_DIRECTORIES(.. ${PAM_INCLUDE_DIR})

ADD_LIBRARY(pam_trihlav SHARED pam_trihlav.cpp )
SET_TARGET_PROPERTIES(pam_trihlav PROPERTIES PREFIX "")

# Ubuntu hardcoded - needs to be detected
SET(PAM_MODULES_DIR /lib/x86_64-linux-gnu/security )

INSTALL(TARGETS pam_trihlav LIBRARY DESTINATION ${PAM_MODULES_DIR})
