cmake_minimum_required(VERSION 3.16)

project(
  idle-mmorpg-editor
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

set(SOURCES main.cpp)

set(QML_FILES qml/Main.qml)

qt_add_executable(${PROJECT_NAME} ${SOURCES})

qt_add_qml_module(
  ${PROJECT_NAME}
  URI
  editor
  VERSION
  1.0
  QML_FILES
  ${QML_FILES})

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES MACOSX_BUNDLE TRUE
             WIN32_EXECUTABLE TRUE
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Quick)

include(GNUInstallDirs)
install(
  TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
