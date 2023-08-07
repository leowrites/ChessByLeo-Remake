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


include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${LIB_PATH}/raygui/src)

add_executable(${PROJECT_NAME}
        main.cpp
        entity/player/Player.h
        entity/player/Player.cpp
        entity/piece/Piece.h
        entity/piece/Piece.cpp
        entity/Sprite.h
        entity/Sprite.cpp
        entity/Game.h
        entity/GameConfiguration.h
        entity/GameConfiguration.cpp
        entity/Game.cpp
        entity/board/Board.h
        entity/board/Board.cpp
        entity/Renderable.h
        entity/Renderable.cpp
        system/RenderSystem.h
        system/SystemManager.h
        system/SystemManager.cpp
        system/RenderSystem.cpp
        system/PlayerMouseDragSystem.h
        view/HomeView.h
        view/HomeView.cpp
        utility/utility.h
        utility/utility.cpp
        view/LoadingView.h
        view/LoadingView.cpp
        view/GameConfigView.h
        view/GameConfigView.cpp
        view/InGameView.h
        view/InGameView.cpp
        texture/asset.h
        utility/move_validators/MoveValidator.h
        utility/move_validators/PawnMoveValidator.cpp
        utility/move_validators/Validators.cpp 
        utility/move_validators/KnightMoveValidator.h
        utility/move_validators/KnightMoveValidator.cpp 
        utility/move_validators/RookMoveValidator.h 
        utility/move_validators/QueenMoveValidator.h 
        utility/move_validators/QueenMoveValidator.cpp 
        utility/move_validators/BishopMoveValidator.h 
        utility/move_validators/BishopMoveValidator.cpp 
        utility/move_validators/KingMoveValidator.h 
        utility/move_validators/KingMoveValidator.cpp 
        utility/move_validators/ValidatorHelper.h 
        utility/move_validators/ValidatorHelper.cpp 
        utility/move_validators/RookMoveValidator.cpp
        utility/check_validator/CheckValidator.h
        utility/check_validator/CheckValidator.cpp
        utility/check_validator/CheckmateValidator.h
        utility/check_validator/CheckmateValidator.cpp)

target_link_libraries(${PROJECT_NAME}  raylib)
