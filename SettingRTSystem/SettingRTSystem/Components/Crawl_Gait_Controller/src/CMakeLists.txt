set(FourLeggedRobotDir ../Four_legged_Robot)

set(comp_srcs Crawl_Gait_Controller.cpp ${FourLeggedRobotDir}/Four_legged_Robot.cpp ${FourLeggedRobotDir}/CrawlGait.cpp ${FourLeggedRobotDir}/Direction_Object.cpp ${FourLeggedRobotDir}/IntermittentCrawlGait.cpp ${FourLeggedRobotDir}/Leg_Object.cpp ${FourLeggedRobotDir}/Stability_Margin.cpp ${FourLeggedRobotDir}/GaitBase.cpp ${FourLeggedRobotDir}/Four_legged_Robot.h ${FourLeggedRobotDir}/CrawlGait.h ${FourLeggedRobotDir}/Direction_Object.h ${FourLeggedRobotDir}/IntermittentCrawlGait.h ${FourLeggedRobotDir}/Leg_Object.h ${FourLeggedRobotDir}/Stability_Margin.h ${FourLeggedRobotDir}/GaitBase.h ${FourLeggedRobotDir}/Body_Object.cpp ${FourLeggedRobotDir}/Body_Object.h ${FourLeggedRobotDir}/TrotGait.cpp ${FourLeggedRobotDir}/TrotGait.h )
set(standalone_srcs Crawl_Gait_ControllerComp.cpp)

set(EIGEN_DIRECTORIY ${EIGEN_DIRECTORIY} CACHE PATH "set EIGEN_DIRECTORIY ")

if(NOT EIGEN_DIRECTORIY)
	message(FATAL_ERROR "Please set EIGEN_DIRECTORIY.")
endif()


set(EigenDir ${EIGEN_DIRECTORIY})

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

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR}/idl)
include_directories(${OPENRTM_INCLUDE_DIRS})
include_directories(${OMNIORB_INCLUDE_DIRS})
include_directories(${EigenDir})
include_directories(${FourLeggedRobotDir})
add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})

MAP_ADD_STR(comp_hdrs "../" comp_headers)

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
  ${comp_headers} ${ALL_IDL_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
if(NOT TARGET ALL_IDL_TGT)
  add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES})

add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS})
target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES})

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT component
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT component
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT component)
install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)
