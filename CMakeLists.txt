cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_PREFIX_PATH ${qt_dir})
list(APPEND CMAKE_PREFIX_PATH ${qtc_dir})

project(CuteDiscordPresence)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(DISCORD_RPC_LIB "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/win64-dynamic/lib/discord-rpc.lib")
    set(DISCORD_RPC_LIB_PATH "${CMAKE_SOURCE_DIR}/dependencies/win64-dynamic/lib")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/win64-dynamic/include")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(DISCORD_RPC_LIB "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/linux-dynamic/lib/libdiscord-rpc.so")
    set(DISCORD_RPC_LIB_PATH "${CMAKE_SOURCE_DIR}/dependencies/linux-dynamic/lib")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/linux-dynamic/include")
endif()

find_package(QtCreator REQUIRED COMPONENTS Core ProjectExplorer)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core5Compat Widgets)
set(QtX Qt${QT_VERSION_MAJOR})

# Add a CMake option that enables building your plugin with tests.
# You don't want your released plugin binaries to contain tests,
# so make that default to 'NO'.
# Enable tests by passing -DWITH_TESTS=ON to CMake.
option(WITH_TESTS "Builds with tests" NO)

if(WITH_TESTS)
  # Look for QtTest
  find_package(${QtX} REQUIRED COMPONENTS Test)

  # Tell CMake functions like add_qtc_plugin about the QtTest component.
  set(IMPLICIT_DEPENDS Qt::Test)

  # Enable ctest for auto tests.
  enable_testing()
endif()

link_directories(${DISCORD_RPC_LIB_PATH})

add_qtc_plugin(CuteDiscordPresence
  PLUGIN_DEPENDS
    QtCreator::Core
    QtCreator::ProjectExplorer
  DEPENDS
    ${QtX}::Widgets
    QtCreator::ExtensionSystem
    QtCreator::Utils
    ${DISCORD_RPC_LIB}
  SOURCES
    .github/workflows/build_cmake.yml
    .github/workflows/README.md
    README.md
    CuteDiscordPresence.json.in
)

extend_qtc_plugin(CuteDiscordPresence
  SOURCES
  .github/workflows/build_cmake.yml
  .github/workflows/README.md
  README.md
  cutediscordpresence.cpp
  cutediscordpresence.h
)

target_link_libraries(CuteDiscordPresence PRIVATE ${DISCORD_RPC_LIB})

add_custom_command(TARGET CuteDiscordPresence POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${DISCORD_RPC_LIB}
            $<TARGET_FILE_DIR:CuteDiscordPresence>
    COMMENT "Copying discord-rpc library to output directory"
)
