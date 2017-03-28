set(hdrs ExcelControlpy.h
    PARENT_SCOPE
    SpreadSheetSVC_impl.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

