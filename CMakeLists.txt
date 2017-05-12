###############################################################################
#
# Trihlav auth server main directory
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
IF(POLICY CMP0048)
   CMAKE_POLICY(SET CMP0048 NEW)
ENDIF(POLICY CMP0048)
PROJECT(trihlav VERSION 0.0.1)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cmake" "${CMAKE_CURRENT_SOURCE_DIR}")

INCLUDE(GetGitRevisionDescription)
###############################################################################

INCLUDE(FindThreads)

###############################################################################
#
# Boost & threads
#
#SET(Boost_USE_STATIC_LIBS       ON) # only find static libs
SET(Boost_USE_MULTITHREADED      ON)
SET(Boost_USE_STATIC_RUNTIME    OFF)
FIND_PACKAGE(Boost 1.54.0 COMPONENTS  log log_setup date_time filesystem system regex thread locale serialization REQUIRED)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
ADD_DEFINITIONS(-D_REENTRANT -DBOOST_SPIRIT_THREADSAFE)
###############################################################################

###############################################################################
#
# Find PAM
#
SET(PAM_FIND_REQUIRED 1)
include(FindPAM)
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
# Yubikey
#
FIND_LIBRARY(YUBIKEY_LIB yubikey /usr/lib64 /usr/lib )
###############################################################################

###############################################################################
#
# C++14
#
IF (CMAKE_VERSION VERSION_LESS "3.1")
  IF (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET (CMAKE_CXX_FLAGS "--std=gnu++14 ${CMAKE_CXX_FLAGS}")
  ENDIF ()
ELSE ()
  SET (CMAKE_CXX_STANDARD 14)
ENDIF ()
###############################################################################

###############################################################################
#
# Global Unit Testing
#
ENABLE_TESTING()

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")
###############################################################################

###############################################################################
#
# xgettext
#
# xgettext --keyword=translate:1,1t --keyword=translate:1c,2,2t       \
#          --keyword=translate:1,2,3t --keyword=translate:1c,2,3,4t   \
#          --keyword=gettext:1 --keyword=pgettext:1c,2                \
#          --keyword=ngettext:1,2 --keyword=npgettext:1c,2,3          \
#          source_file_1.cpp ... source_file_N.cpp
###############################################################################
FIND_PACKAGE(Gettext)
###############################################################################
#
# Start CPack
#
SET(CPACK_GENERATOR "RPM;DEB")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Trihlav OTP Authentification server")
SET(CPACK_PACKAGE_VENDOR "Peter Grobarcik")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
SET(CPACK_PACKAGE_CONTACT "coder.peter.grobarcik@gmail.com")
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
  SET(CPACK_NSIS_CONTACT "coder.peter.grobarcik@gmail.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_STRIP_FILES "bin/trihlavsrv")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/main/script/post_install.sh")
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
FIND_PATH(WT_RESOURCES NAMES ajax-loading.gif PATHS /usr/share/wt/resources /opt/wt/resources /usr/share/Wt/resources )
IF(${WT_RESOURCES} EQUAL WT_RESOURCES-NOTFOUND)
   MESSAGE( FATAL_ERROR "Wt resource directory not found." )
ELSE(${WT_RESOURCES} EQUAL WT_RESOURCES-NOTFOUND)
   MESSAGE( STATUS "Found the Wt resource directory =${WT_RESOURCES}." )
ENDIF(${WT_RESOURCES} EQUAL WT_RESOURCES-NOTFOUND)
###############################################################################

# Our only dependency is OpenSSL
find_package(OpenSSL REQUIRED)
#include_directories(${OPENSSL_INCLUDE_DIR})

ADD_SUBDIRECTORY(src/main/cpp/trihlavSrv)
ADD_SUBDIRECTORY(src/main/cpp/trihlavLib)
ADD_SUBDIRECTORY(src/main/cpp/pam)
ADD_SUBDIRECTORY(src/main/script)
ADD_SUBDIRECTORY(src/main/resources)
ADD_SUBDIRECTORY(src/test/cpp)
