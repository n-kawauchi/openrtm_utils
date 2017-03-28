set(hdrs RMC.h
	Body.h
	BodyMenu.h
	Bodypages.h
	Camera.h
	CameraMenu.h
	Camerapages.h
	diagramscene.h
	glbox.h
	Joint.h
	JointMenu.h
	Jointpages.h
	mainwindow.h
	Sensor.h
	SensorMenu.h
	Sensorpages.h
	ObjectData.h
    PARENT_SCOPE
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

