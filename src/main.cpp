#include <iostream>
#include <raylib.h>
#include "levels/Environment.hpp"
int main() {
    const int screenWidth = 1024;
    const int screenHeight = 896;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    EnvironmentObject& ground = Ground::GetGround();

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
        ground.render();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}