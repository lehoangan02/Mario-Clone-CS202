// #include "../Application.hpp"

// int main() {
//     SetConfigFlags(FLAG_MSAA_4X_HINT);
//     InitWindow(1024, 768, "Game Window");
//     SetWindowState(FLAG_WINDOW_RESIZABLE);
//     ResourceManager::GetInstance()->LoadResources();
//     SetTargetFPS(60);
//     Application app;
//     app.run();
// }

#include "../characters/Enemy.hpp"
#include "raylib.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 768, "Game Window");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    
    KoopaTroopa goomba({300, 300});
    // PiranhaPlant piranha({200, 200});
    // KoopaTroopa koopa({400, 400});
    // ShyGuy shy({500, 500});
    // InversePiranhaPlant inversePiranha({600, 600});
    // Lakitu lakitu({100, 100});
    Texture2D texture = LoadTexture("assets/textures/quit.png");
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleLines(300, 300, 42, 58, RED);

        DrawTextureEx(texture, {100, 100}, 0.0f, 0.13, WHITE);
        goomba.update(0.01f);
        goomba.render();
        if (IsKeyPressed(KEY_SPACE)) {
            goomba.hit();
        }
        EndDrawing();
    }
    CloseWindow();
}

// #include "../Application.hpp"

// #include "../levels/Level.hpp"
// int main() {
//     const int screenWidth = 1024;
//     const int screenHeight = 896;

//     InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

//     SetTargetFPS(60);
//     LevelFactory& factory = LevelFactory::GetLevelFactory();
//     Level* level = factory.CreateLevel(LevelFactory::LEVEL_101);

//     while (!WindowShouldClose()) {

//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         if(IsKeyPressed(KEY_P)) {
//             level = factory.CreateLevel(LevelFactory::LEVEL_103);
//         }
//         level->update(GetFrameTime());

//         level->render();
//         EndDrawing();
//     }

//     CloseWindow();
// }
