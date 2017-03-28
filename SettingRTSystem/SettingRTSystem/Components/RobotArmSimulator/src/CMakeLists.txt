set(arm_file_path ../RobotArm)
set(defreturnid_file_path thirdparty/RTM_ORiN_Converter_CRD)

set(ODE_DIRECTORIY ${ODE_DIRECTORIY} CACHE PATH "set ODE_DIRECTORIY ")

if(NOT ODE_DIRECTORIY)
	message(FATAL_ERROR "Please set ODE_DIRECTORIY.")
endif()


set(EIGEN_DIRECTORIY ${EIGEN_DIRECTORIY} CACHE PATH "set EIGEN_DIRECTORIY ")

if(NOT EIGEN_DIRECTORIY)
	message(FATAL_ERROR "Please set EIGEN_DIRECTORIY.")
endif()


set(ODEDir ${ODE_DIRECTORIY})
set(EigenDir ${EIGEN_DIRECTORIY})


#set(ODEDir C:/ode-0.13)
#set(EigenDir C:/eigen-eigen-bdd17ee3b1b3)
set(comp_srcs RobotArmSimulator.cpp ManipulatorCommonInterface_CommonSVC_impl.cpp ManipulatorCommonInterface_MiddleLevelSVC_impl.cpp ${arm_file_path}/RobotArm.cpp DrawThread.cpp SimulatorObj.cpp ${ODEDir}/drawstuff/src/resources.rc searchFile.cpp )
set(standalone_srcs RobotArmSimulatorComp.cpp)


set(ODELIB optimized;ode;debug;oded;optimized;drawstuff;debug;drawstuffd;;user32.lib;winmm;opengl32;glu32)

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
include_directories(${arm_file_path})
include_directories(${defreturnid_file_path})

include_directories(${EigenDir})
include_directories(${ODEDir}/include)

add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})

MAP_ADD_STR(comp_hdrs "../" comp_headers)

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})
link_directories(${ODEDir}/lib/Release)
link_directories(${ODEDir}/lib/Debug)

add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
  ${comp_headers} ${ALL_IDL_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
if(NOT TARGET ALL_IDL_TGT)
  add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES} ${ODELIB} shlwapi.lib)

add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS})
target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES} ${ODELIB} shlwapi.lib)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT component
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT component
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT component)
install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)
