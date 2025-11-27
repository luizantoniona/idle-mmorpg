set(MODULE_NAME Components)

set(QML_FILES_LIST
  CreatureList.qml
  ItemList.qml
  SpellList.qml
)

set(RESOURCES
  qmldir
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
  RESOURCES
  ${RESOURCES}
)
