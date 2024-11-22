#include "raylib.h"
#include <iostream>
#include "characters/Character.h"
#include "levels/Level.hpp"
#include "animation/Animation.h"
int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 896;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    LevelFactory& factory = LevelFactory::GetLevelFactory();
    Level* level = factory.CreateLevel(LevelFactory::LEVEL_101);
	Texture t = LoadTexture("../assets/textures/mario.png");
	Character player(&t, Vector2{ 4, 1 }, 2.0f, 4.0f, 3.0f);

    float deltatime = 0.5f;
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second



    ///nextime you here rember to fix the deltatime when u suspense the mario 
	// and also make animation.h and animation.cpp in the same folder
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLUE);
        player.Draw();
		player.Update(deltatime);
        level->render();
        DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);
        DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
