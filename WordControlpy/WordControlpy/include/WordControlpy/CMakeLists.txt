set(hdrs WordControlpy.h
    PARENT_SCOPE
    WriterSVC_impl.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

