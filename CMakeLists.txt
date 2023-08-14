cmake_minimum_required(VERSION 3.25)
project(ChessByLeo_Remake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_OSX_ARCHITECTURES "arm64")

SET(INCLUDE_PATH "include")
SET(LIB_PATH "lib")

add_definitions( -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} )

include_directories(${INCLUDE_PATH})
include_directories(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
message(${CMAKE_CURRENT_SOURCE_DIR}/${LIB_PATH}/raylib/libraylib.a)
target_link_libraries(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_PATH}/raylib/libraylib.a" "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")