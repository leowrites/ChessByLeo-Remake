//
// Created by Siqi Liu on 2023-07-13.
//

#include <iostream>
#include "raylib.h"
#include "entity/Game.h"
#include "view/HomeView.h"
#include "view/LoadingView.h"
#include "view/GameConfigView.h"

int main()
{
    std::cout << "Hello World" << std::endl;
    const int screenWidth{ 800 };
    const int screenHeight{ 800 };
    Vector2 mousePosition;
    Chess::GameState currGameState { Chess::GameState::Home };
    InitWindow(screenWidth, screenHeight, "Chess By Leo V2");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        mousePosition = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (currGameState)
        {
            case Chess::GameState::Loading:
                Chess::LoadingView::Render(screenWidth, screenHeight);
                break;
            case Chess::GameState::Home:
                Chess::HomeView::Render(screenWidth, screenHeight, mousePosition);
                Chess::HomeView::HandleMouseClick(mousePosition, currGameState);
                break;
            case Chess::GameState::Configuration:
                break;
            case Chess::GameState::InGame:
                break;
            case Chess::GameState::Paused:
                break;
            case Chess::GameState::GameOver:
                break;
            case Chess::GameState::Statistics:
                break;
        }

        EndDrawing();
    }
    CloseWindow();
}