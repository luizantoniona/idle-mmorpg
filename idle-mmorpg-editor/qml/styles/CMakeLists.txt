set(MODULE_NAME Styles)

set(QML_FILES_LIST
  Colors.qml
)

set_source_files_properties(
  ${CMAKE_CURRENT_SOURCE_DIR}/Colors.qml
  PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(
  ${MODULE_NAME}
  URI
  ${MODULE_NAME}
  VERSION
  1.0
  STATIC
  PLUGIN_TARGET
  ${MODULE_NAME}Plugin
  QML_FILES
  ${QML_FILES_LIST}
)
