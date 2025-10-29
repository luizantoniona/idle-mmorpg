cmake_minimum_required(VERSION 3.16)

project(idle-rpg-server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(
  GLOB_RECURSE
  SOURCES
  Commons/*.cpp
  Core/*.cpp
  Database/*.cpp
  Helper/*.cpp
  Model/*.cpp
  Network/*.cpp
  Repository/*.cpp)

file(
  GLOB_RECURSE
  HEADERS
  Commons/*.h
  Core/*.h
  Database/*.h
  Helper/*.h
  Model/*.h
  Network/*.h
  Repository/*.h)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})

find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

if(WIN32)
  find_package(unofficial-sqlite3 CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::sqlite3::sqlite3)
endif(WIN32)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SQL_FILES Resources/*.sql)

source_group("SQL Files" FILES ${SQL_FILES})

target_sources(${PROJECT_NAME} PRIVATE ${SQL_FILES})

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})

include(GNUInstallDirs)
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
