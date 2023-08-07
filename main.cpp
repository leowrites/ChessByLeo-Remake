//
// Created by Siqi Liu on 2023-07-13.
//

#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "entity/Game.h"
#include "view/HomeView.h"
#include "view/LoadingView.h"
#include "view/GameConfigView.h"
#include "view/InGameView.h"

int main()
{
    const int screenWidth{ 800 };
    const int screenHeight{ 800 };
    Vector2 mousePosition;
    Chess::GameState currGameState { Chess::GameState::Home };
    Chess::GameConfiguration gameConfiguration {};
    std::shared_ptr<Chess::Game> gamePtr { nullptr };
    InitWindow(screenWidth, screenHeight, "Chess By Leo V2");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        mousePosition = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (currGameState)
        {
            // skipping Loading View for now to get to the game
            case Chess::GameState::Loading:
                Chess::LoadingView::Render(screenWidth, screenHeight);
                // initialize the game
                Chess::LoadingView::InitializeGame(gamePtr, gameConfiguration);
                Chess::LoadingView::Update(currGameState);
                break;
            case Chess::GameState::Home:
                Chess::HomeView::Render(screenWidth, screenHeight, mousePosition);
                Chess::HomeView::Update(mousePosition, currGameState);
                break;
            case Chess::GameState::Configuration:
                Chess::GameConfigView::Render();
                Chess::GameConfigView::Update(mousePosition, gameConfiguration, currGameState);
                break;
            case Chess::GameState::InGame:
                Chess::InGameView::Update(gamePtr, currGameState);
                Chess::InGameView::Render(screenWidth, screenHeight, gamePtr);
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