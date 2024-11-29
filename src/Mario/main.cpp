#include "raylib.h"
#include <iostream>
#include "../characters/Character.h"
#include "../levels/Level.hpp"
#include "../animation/Animation.h"
int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    LevelFactory& factory = LevelFactory::GetLevelFactory();
    Level* level = factory.CreateLevel(LevelFactory::LEVEL_101);
	Character* player = CharacterFactory::createCharacter(MARIO);
    level->attachPlayer(player);
    float deltatime;
	SetTargetFPS(60); 
    while (!WindowShouldClose())
    {
        deltatime = GetFrameTime();
        level->update(deltatime);
        BeginDrawing();
        ClearBackground(Color{105, 147, 245, 255});
        level->render();
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
