# ECandStateSharedComposite CMake config file
#
# This file sets the following variables:
# ECandStateSharedComposite_FOUND - Always TRUE.
# ECandStateSharedComposite_INCLUDE_DIRS - Directories containing the ECandStateSharedComposite include files.
# ECandStateSharedComposite_IDL_DIRS - Directories containing the ECandStateSharedComposite IDL files.
# ECandStateSharedComposite_LIBRARIES - Libraries needed to use ECandStateSharedComposite.
# ECandStateSharedComposite_DEFINITIONS - Compiler flags for ECandStateSharedComposite.
# ECandStateSharedComposite_VERSION - The version of ECandStateSharedComposite found.
# ECandStateSharedComposite_VERSION_MAJOR - The major version of ECandStateSharedComposite found.
# ECandStateSharedComposite_VERSION_MINOR - The minor version of ECandStateSharedComposite found.
# ECandStateSharedComposite_VERSION_REVISION - The revision version of ECandStateSharedComposite found.
# ECandStateSharedComposite_VERSION_CANDIDATE - The candidate version of ECandStateSharedComposite found.

message(STATUS "Found ECandStateSharedComposite-1.0.0")
set(ECandStateSharedComposite_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(ECandStateSharedComposite_INCLUDE_DIRS
#    "C:/OpenRTM-aist/include/ecandstatesharedcomposite-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(ECandStateSharedComposite_IDL_DIRS
#    "C:/OpenRTM-aist/include/ecandstatesharedcomposite-1/idl")
set(ECandStateSharedComposite_INCLUDE_DIRS
    "C:/OpenRTM-aist/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(ECandStateSharedComposite_IDL_DIRS
    "C:/OpenRTM-aist/include//idl")


if(WIN32)
    set(ECandStateSharedComposite_LIBRARIES
        "C:/OpenRTM-aist/components/lib/ecandstatesharedcomposite.lib"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(ECandStateSharedComposite_LIBRARIES
        "C:/OpenRTM-aist/components/lib/ecandstatesharedcomposite.dll"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(ECandStateSharedComposite_DEFINITIONS ${<dependency>_DEFINITIONS})

set(ECandStateSharedComposite_VERSION 1.0.0)
set(ECandStateSharedComposite_VERSION_MAJOR 1)
set(ECandStateSharedComposite_VERSION_MINOR 0)
set(ECandStateSharedComposite_VERSION_REVISION 0)
set(ECandStateSharedComposite_VERSION_CANDIDATE )

