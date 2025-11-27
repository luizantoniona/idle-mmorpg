set(QML_STYLES_FILES
  Colors.qml
)

qt_add_qml_module(
  Styles
  URI
  Styles
  VERSION
  1.0
  TARGET_PATH
  Styles
  OUTPUT_DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/Styles
  QML_FILES
  ${QML_STYLES_FILES}
)
