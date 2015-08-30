###############################################################################
#
cmake_minimum_required(VERSION 2.6)

project(trihlavsrv)
set (WT_CONNECTOR "wtfcgi" CACHE STRING "Connector used (wthttp or wtfcgi)")
add_subdirectory(src)
