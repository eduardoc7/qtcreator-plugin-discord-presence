if(TARGET discord-rpc)
  return()
endif()

if(CMAKE_SYSTEM_NAME
   STREQUAL
   "Windows")
  set(DISCORD_RPC_INCLUDE_HINT
      "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/discord-rpc/win64-static/include"
  )
  set(DISCORD_RPC_LIB_HINT
      "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/discord-rpc/win64-static/lib/")
elseif(
  CMAKE_SYSTEM_NAME
  STREQUAL
  "Linux")
  set(DISCORD_RPC_INCLUDE_HINT
      "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/discord-rpc/linux-dynamic/include"
  )
  set(DISCORD_RPC_LIB_HINT
      "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/discord-rpc/linux-dynamic/lib")
else()
  message(FATAL_ERROR "Unsupported system")
endif()

find_path(
  DISCORD_RPC_INCLUDE_DIR
  NAMES discord_register.h discord_rpc.h
  PATH_SUFFIXES include
  HINTS ${DISCORD_RPC_INCLUDE_HINT} REQUIRED)

find_library(
  DISCORD_RPC_LIB
  NAMES discord-rpc
  HINTS ${DISCORD_RPC_LIB_HINT}
  PATH_SUFFIXES lib REQUIRED)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  discord-rpc
  DEFAULT_MSG
  DISCORD_RPC_INCLUDE_DIR
  DISCORD_RPC_LIB)

if(discord-rpc_FOUND)
  if(NOT
     TARGET
     discord-rpc)
    add_library(
      discord-rpc
      UNKNOWN
      IMPORTED)
    set_target_properties(
      discord-rpc
      PROPERTIES IMPORTED_LOCATION "${DISCORD_RPC_LIB}"
                 INTERFACE_INCLUDE_DIRECTORIES "${DISCORD_RPC_INCLUDE_DIR}")
  endif()
endif()

mark_as_advanced(DISCORD_RPC_INCLUDE_DIR DISCORD_RPC_LIB)

set_package_properties(
  discord-rpc PROPERTIES
  URL "https://github.com/discord/discord-rpc"
  DESCRIPTION "Discord RPC library")
