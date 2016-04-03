cmake_minimum_required(VERSION 3.2)
# Configuration du projet
project(Planet\ X)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

file(
	GLOB_RECURSE
	SOURCE_FILES
	src/*
)

add_executable(Planet_X ${SOURCE_FILES})
target_link_libraries(Planet_X ${SDL2_LIBRARY})

