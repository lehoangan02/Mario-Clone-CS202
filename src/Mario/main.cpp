#include "raylib.h"
#include <iostream>
#include "../characters/Character.h"
#include "../levels/Level.hpp"
#include "../animation/Animation.h"
#include "../Obstacle/Obstacle.h"

int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    Texture2D obstacleTexture = LoadTexture("assets/textures/brick.png");
    DynamicObstacle dynamicObstacle(Vector2{ 300, 300 }, Vector2{ 50, 50 }, obstacleTexture, Vector2{ 200, 0 });
    
    LevelFactory& factory = LevelFactory::GetLevelFactory();
    Level* level = factory.CreateLevel(LevelFactory::LEVEL_101);
    Texture t = LoadTexture("assets/textures/mario.png");
	Character player(&t, Vector2{ 10, 1 }, 0.1f, 4.0f, 3.0f);
    player.setPosition(Vector2{20 , 0});
    level->attachPlayer(&player);
    float deltatime;
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())
    {
        deltatime = GetFrameTime();

        dynamicObstacle.Update(deltatime);


        level->update(deltatime);



        BeginDrawing();
        ClearBackground(Color{105, 147, 245, 255});

        dynamicObstacle.Draw();
        level->render();
        // DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);
        // DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
