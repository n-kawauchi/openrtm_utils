set(hdrs Scope.h
	mainwindow.h
	panel.h
	plot.h
	settings.h
    PARENT_SCOPE
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

