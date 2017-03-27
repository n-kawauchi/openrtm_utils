# Install script for directory: C:/workspace/MSMTest/SettingRTSystem/rtcdControl/idl

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/OpenRTM-aist")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "idl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/include/rtcdcontrol-1/idl" TYPE FILE FILES
    "C:/workspace/MSMTest/SettingRTSystem/rtcdControl/idl/rtcControl.idl"
    "C:/workspace/MSMTest/SettingRTSystem/rtcdControl/idl/BasicDataType.idl"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/include/rtcdcontrol-1/rtcdcontrol/idl" TYPE FILE FILES
    "C:/workspace/MSMTest/SettingRTSystem/rtcdControl/idl/rtcControl.hh"
    "C:/workspace/MSMTest/SettingRTSystem/rtcdControl/idl/BasicDataType.hh"
    )
endif()

