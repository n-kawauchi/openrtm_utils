set(subfile_path ../RTMath)

set(comp_srcs Scope.cpp mainwindow.cpp panel.cpp plot.cpp ${subfile_path}/RTMath.cpp )
set(standalone_srcs ScopeComp.cpp)


set(CMAKE_AUTOMOC ON)
#set(QWTDir C:/qwt-6.1.2)

set(QWT_DIRECTORIY ${QWT_DIRECTORIY} CACHE PATH "set QWT_DIRECTORIY ")

if(NOT QWT_DIRECTORIY)
	message(FATAL_ERROR "Please set QWT_DIRECTORIY.")
endif()

set(QWTDir ${QWT_DIRECTORIY})

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
include_directories(${subfile_path})


include_directories(${QWTDir}/src)

add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})


add_definitions(-DQWT_DLL)
add_definitions(-DNOMINMAX)



MAP_ADD_STR(comp_hdrs "../" comp_headers)

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})

link_directories(${QWTDir}/lib)

qt5_wrap_cpp(moc_mainwindow.cpp mainwindow.h)
qt5_wrap_cpp(moc_panel.cpp panel.h)
qt5_wrap_cpp(moc_plot.cpp plot.h)


add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
  ${comp_headers} ${ALL_IDL_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
if(NOT TARGET ALL_IDL_TGT)
  add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES} qwt.lib)

QT5_USE_MODULES(${PROJECT_NAME} Widgets PrintSupport OpenGL Svg Gui Test Concurrent Core)



add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS})
target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES} qwt.lib)


QT5_USE_MODULES(${PROJECT_NAME}Comp Widgets PrintSupport OpenGL Svg Gui Test Concurrent Core)



install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT component
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT component
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT component)
install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)
