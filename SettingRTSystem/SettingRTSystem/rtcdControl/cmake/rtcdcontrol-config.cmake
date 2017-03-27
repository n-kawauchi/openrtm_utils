# rtcdControl CMake config file
#
# This file sets the following variables:
# rtcdControl_FOUND - Always TRUE.
# rtcdControl_INCLUDE_DIRS - Directories containing the rtcdControl include files.
# rtcdControl_IDL_DIRS - Directories containing the rtcdControl IDL files.
# rtcdControl_LIBRARIES - Libraries needed to use rtcdControl.
# rtcdControl_DEFINITIONS - Compiler flags for rtcdControl.
# rtcdControl_VERSION - The version of rtcdControl found.
# rtcdControl_VERSION_MAJOR - The major version of rtcdControl found.
# rtcdControl_VERSION_MINOR - The minor version of rtcdControl found.
# rtcdControl_VERSION_REVISION - The revision version of rtcdControl found.
# rtcdControl_VERSION_CANDIDATE - The candidate version of rtcdControl found.

message(STATUS "Found rtcdControl-1.0.0")
set(rtcdControl_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(rtcdControl_INCLUDE_DIRS
#    "C:/OpenRTM-aist/include/rtcdcontrol-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(rtcdControl_IDL_DIRS
#    "C:/OpenRTM-aist/include/rtcdcontrol-1/idl")
set(rtcdControl_INCLUDE_DIRS
    "C:/OpenRTM-aist/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(rtcdControl_IDL_DIRS
    "C:/OpenRTM-aist/include//idl")


if(WIN32)
    set(rtcdControl_LIBRARIES
        "C:/OpenRTM-aist/components/lib/rtcdcontrol.lib"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(rtcdControl_LIBRARIES
        "C:/OpenRTM-aist/components/lib/rtcdcontrol.dll"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(rtcdControl_DEFINITIONS ${<dependency>_DEFINITIONS})

set(rtcdControl_VERSION 1.0.0)
set(rtcdControl_VERSION_MAJOR 1)
set(rtcdControl_VERSION_MINOR 0)
set(rtcdControl_VERSION_REVISION 0)
set(rtcdControl_VERSION_CANDIDATE )

