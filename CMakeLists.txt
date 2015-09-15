###############################################################################
# Trihlav auth server main directory
cmake_minimum_required(VERSION 2.6)

project(trihlavsrv)

###############################################################################
# Start CPack
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
include(CPack)

# end CPack
###############################################################################

###############################################################################
# Wt toolkit
FIND_PACKAGE( Wt REQUIRED )
SET (WT_CONNECTOR "wtfcgi" CACHE STRING "Connector used (wthttp or wtfcgi)")
# end Wt
###############################################################################

add_subdirectory(src/main/cpp/trihlavSrv)
add_subdirectory(src/main/resources)

