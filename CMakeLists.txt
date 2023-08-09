cmake_minimum_required(VERSION 3.25)
project(ChessByLeo_Remake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_OSX_ARCHITECTURES "arm64")

SET(LIB_PATH "includes")

SET(RAYLIB_VERSION 4.5.0)
FIND_PACKAGE(raylib ${RAYLIB_VERSION})

if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()


add_definitions( -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} )

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${LIB_PATH}/raygui/src)

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
message(${CMAKE_CURRENT_SOURCE_DIR}/assets/)
target_link_libraries(${PROJECT_NAME}  raylib)
