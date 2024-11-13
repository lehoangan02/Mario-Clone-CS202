#include "raylib.h"
#include <iostream>
#include "../characters/Character.h"
#include "../levels/Level.hpp"

int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 896;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    characterFactory Factory;
    character* mainChar = Factory.createCharacter(characterType::MARIO);
    LevelFactory& factory = LevelFactory::GetLevelFactory();
    Level* level = factory.CreateLevel(LevelFactory::LEVEL_101);
    SetTargetFPS(60);
    int framesCounter = 0;
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLUE);
        mainChar->render();
        mainChar->controller(framesCounter);
        level->render();
        DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);
        DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
