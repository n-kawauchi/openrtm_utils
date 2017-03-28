add_subdirectory(RasPiMouseController_DistanceSensor)

MAP_ADD_STR(hdrs "${PROJECT_NAME}/" headers)
set(headers ${headers} PARENT_SCOPE)
