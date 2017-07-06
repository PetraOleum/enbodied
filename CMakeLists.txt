cmake_minimum_required(VERSION 3.7)

project(enbodied)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/main.cpp
	${CMAKE_SOURCE_DIR}/enbodiedapp.cpp
)

add_executable(enbodied ${SOURCE_FILES})
target_link_libraries(enbodied ${SDL2_LIBRARIES})

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
#	EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
#		${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
#		${CMAKE_SOURCE_DIR}/compile_commands.json
#	)
#ENDIF()

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
	EXECUTE_PROCESS( COMMAND ln -sfn ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
	)
ENDIF()
