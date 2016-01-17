###############################################################################
#
# Trihlav auth server main directory
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
IF(POLICY CMP0048)
   CMAKE_POLICY(SET CMP0048 NEW)
ENDIF(POLICY CMP0048)
PROJECT(trihlav VERSION 0.0.1)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cmake")

INCLUDE(GetGitRevisionDescription)
###############################################################################

FIND_PACKAGE (Threads)

###############################################################################
#
# Boost & threads
#
#SET(Boost_USE_STATIC_LIBS       ON) # only find static libs
SET(Boost_USE_MULTITHREADED      ON)
SET(Boost_USE_STATIC_RUNTIME    OFF)
FIND_PACKAGE(Boost 1.54.0 COMPONENTS  log log_setup date_time filesystem system unit_test_framework thread REQUIRED)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
###############################################################################

###############################################################################
#
# Add a target to generate API documentation with Doxygen
#
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
	CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	ADD_CUSTOM_TARGET(doc
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
	ADD_CUSTOM_TARGET(hack_inst ${CMAKE_COMMAND} -E echo "Hacking install target")
	IF("${CMAKE_GENERATOR}" MATCHES Make)
	    INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_BUILD_TOOL} hack_inst WORKING_DIRECTORY \"${CMAKE_CURRENT_BINARY_DIR}\")")
	ENDIF()
	INSTALL( DIRECTORY ${CMAKE_BINARY_DIR}/doc/ DESTINATION /usr/share/doc/packages/trihlav-${PROJECT_VERSION} )
ENDIF(DOXYGEN_FOUND)
################################################################################

################################################################################
#
# C++11
#
FIND_LIBRARY(YUBIKEY_LIB yubikey /usr/lib64 /usr/lib )
###############################################################################

###############################################################################
#
# C++11
#
IF (CMAKE_VERSION VERSION_LESS "3.1")
  IF (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
  ENDIF ()
ELSE ()
  SET (CMAKE_CXX_STANDARD 11)
ENDIF ()
###############################################################################

###############################################################################
#
# Global Unit Testing
#
ENABLE_TESTING()
###############################################################################

###############################################################################
#
# Start CPack
#
SET(CPACK_GENERATOR "RPM")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Trihlav Authentification server")
SET(CPACK_PACKAGE_VENDOR "Me, myself, and I")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\trihlavsrv.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  SET(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_STRIP_FILES "bin/trihlavsrv")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "trihlavsrv" "Trihlav Server")
INCLUDE(CPack)
# end CPack
###############################################################################

###############################################################################
#
# Wt toolkit
#
FIND_PACKAGE( Wt REQUIRED )
SET (WT_CONNECTOR "wtfcgi" CACHE STRING "Connector used (wthttp or wtfcgi)")
# Find Wt resources
FIND_PATH(WT_RESOURCES NAMES ajax-loading.gif PATHS /usr/share/wt/resources /opt/wt/resources )
IF(${WT_RESOURCES} EQUAL WT_RESOURCES-NOTFOUND)
   MESSAGE( FATAL_ERROR "Wt resource directory not found." )
ELSE(${WT_RESOURCES} EQUAL WT_RESOURCES-NOTFOUND)
   MESSAGE( STATUS "Found the Wt resource directory =${WT_RESOURCES}." )
ENDIF(${WT_RESOURCES} EQUAL WT_RESOURCES-NOTFOUND)
###############################################################################

ADD_SUBDIRECTORY(src/main/cpp/trihlavSrv)
ADD_SUBDIRECTORY(src/main/cpp/trihlavLib)
ADD_SUBDIRECTORY(src/main/resources)
ADD_SUBDIRECTORY(src/test/cpp)
