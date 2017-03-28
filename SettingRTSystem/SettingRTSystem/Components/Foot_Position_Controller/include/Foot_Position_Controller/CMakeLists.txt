set(hdrs Foot_Position_Controller.h
	LeggedRobotSVC_impl.h
    PARENT_SCOPE
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

