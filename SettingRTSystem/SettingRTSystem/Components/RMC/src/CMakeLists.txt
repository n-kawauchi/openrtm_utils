set(comp_srcs RMC.cpp Sensorpages.cpp SensorMenu.cpp Sensor.cpp RMCComp.cpp mainwindow.cpp Jointpages.cpp JointMenu.cpp Joint.cpp glbox.cpp diagramscene.cpp Camerapages.cpp CameraMenu.cpp Camera.cpp Bodypages.cpp BodyMenu.cpp Body.cpp ObjectData.cpp )

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(standalone_srcs RMCComp.cpp RMC.rc)
else(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(standalone_srcs RMCComp.cpp)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")



set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)


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
add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})

add_definitions(-DNOMINMAX)


MAP_ADD_STR(comp_hdrs "../" comp_headers)

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})


qt5_wrap_cpp(moc_BodyMenu.cpp BodyMenu.h)
qt5_wrap_cpp(moc_CameraMenu.cpp CameraMenu.h)
qt5_wrap_cpp(moc_diagramscene.cpp diagramscene.h)
qt5_wrap_cpp(moc_glbox.cpp glbox.h)
qt5_wrap_cpp(moc_mainwindow.cpp mainwindow.h)
qt5_wrap_cpp(moc_SensorMenu.cpp SensorMenu.h)

qt5_add_resources(QRC RMC.qrc)

add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
  ${comp_headers} ${ALL_IDL_SRCS} ${QRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
if(NOT TARGET ALL_IDL_TGT)
  add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES} opengl32.lib glu32.lib)

add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS} ${QRC})
target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES} opengl32.lib glu32.lib)


QT5_USE_MODULES(${PROJECT_NAME} Widgets OpenGL Gui Test Core)
QT5_USE_MODULES(${PROJECT_NAME}Comp Widgets OpenGL Gui Test Core)


install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT component
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT component
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT component)
install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)
