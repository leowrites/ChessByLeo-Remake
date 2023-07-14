//
// Created by Siqi Liu on 2023-07-13.
//

#include <iostream>
#include "raylib.h"
int main()
{
    std::cout << "Hello World" << std::endl;
    const int screenWidth{ 800 };
    const int screenHeight{ 800 };

    InitWindow(screenWidth, screenHeight, "Hello World!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // PlayerMouseDragSystem
        // MoveSystem
        // RenderSystem

        EndDrawing();
    }
    CloseWindow();
}