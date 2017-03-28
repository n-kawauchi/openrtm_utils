cmake_minimum_required (VERSION 2.6)

find_package(OpenRTM HINTS /usr/lib64/openrtm-1.1/cmake)
if(${OpenRTM_FOUND})
  MESSAGE(STATUS "OpenRTM configuration Found")
else(${OpenRTM_FOUND})
  message(STATUS "Use cmake/Modules/FindOpenRTM.cmake in the project")
  list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
  find_package(OpenRTM REQUIRED)
endif(${OpenRTM_FOUND})



if (DEFINED OPENRTM_INCLUDE_DIRS)
  string(REGEX REPLACE "-I" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
endif (DEFINED OPENRTM_INCLUDE_DIRS)

if (DEFINED OPENRTM_LIBRARY_DIRS)
  string(REGEX REPLACE "-L" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
endif (DEFINED OPENRTM_LIBRARY_DIRS)

if (DEFINED OPENRTM_LIBRARIES)
  string(REGEX REPLACE "-l" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
endif (DEFINED OPENRTM_LIBRARIES)



include_directories(${OPENRTM_INCLUDE_DIRS})
include_directories(${OMNIORB_INCLUDE_DIRS})
add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})


link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})


project (rtcd_p)

add_executable (rtcd_p rtcd_p.cpp FileStreamFunc.cpp LoadRTCs.cpp)
target_link_libraries(rtcd_p ${OPENRTM_LIBRARIES})