#include <iostream>
#include <raylib.h>
#include "levels/Level.hpp"
int main() {
    const int screenWidth = 1024;
    const int screenHeight = 896;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    LevelFactory& factory = LevelFactory::GetLevelFactory();
    Level* level = factory.CreateLevel(LevelFactory::LEVEL_101);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
        level->render();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}