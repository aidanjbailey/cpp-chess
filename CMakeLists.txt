cmake_minimum_required( VERSION 3.2 )

project ( cpp-chess )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file( GLOB SRCS src/main.cc src/chess-board/*.cc src/services/*.cc )

include_directories( include src/chess-board src/services/*.h )

add_executable( cpp-chess ${SRCS} )
