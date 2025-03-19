cmake_minimum_required(VERSION 3.10)

project(CuteDiscordPresence)

list(
  APPEND
  CMAKE_PREFIX_PATH
  ${qt_dir})
list(
  APPEND
  CMAKE_PREFIX_PATH
  ${qtc_dir})
list(
  APPEND
  CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
    ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

find_package(
  QtCreator
  COMPONENTS Core
  REQUIRED)

find_package(
  QT
  NAMES
  Qt6
  Qt5
  COMPONENTS Core5Compat Widgets
  REQUIRED)
set(QtX Qt${QT_VERSION_MAJOR})

# Add a CMake option that enables building your plugin with tests. You don't
# want your released plugin binaries to contain tests, so make that default to
# 'NO'. Enable tests by passing -DWITH_TESTS=ON to CMake.
option(
  WITH_TESTS
  "Builds with tests"
  NO)

if(WITH_TESTS)
  # Look for QtTest
  find_package(${QtX} REQUIRED COMPONENTS Test)

  # Tell CMake functions like add_qtc_plugin about the QtTest component.
  set(IMPLICIT_DEPENDS Qt::Test)

  # Enable ctest for auto tests.
  enable_testing()
endif()

add_qtc_plugin(
  CuteDiscordPresence
  PLUGIN_DEPENDS
  QtCreator::Core
  QtCreator::ProjectExplorer
  DEPENDS
  ${QtX}::Widgets
  QtCreator::ExtensionSystem
  QtCreator::Utils
  SOURCES
  .github/workflows/build_cmake.yml
  .github/workflows/README.md
  README.md
  CuteDiscordPresence.json.in)

find_package(discord-rpc REQUIRED)

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/discord-rpc/win64-static/include")

extend_qtc_plugin(
  CuteDiscordPresence
  CONDITION
  TARGET
  discord-rpc
  DEPENDS
  discord-rpc
  SOURCES
  cutediscordpresence.cpp
  cutediscordpresence.h)
