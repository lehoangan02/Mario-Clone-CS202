// #include "../Application.hpp"

// int main() {
//     SetConfigFlags(FLAG_MSAA_4X_HINT);
//     InitWindow(1024, 768, "Game Window");
//     SetWindowState(FLAG_WINDOW_RESIZABLE);
//     ResourceManager::GetInstance()->LoadResources();

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
    
    Goomba goomba({300, 300});
    PiranhaPlant piranha({200, 200});
    KoopaTroopa koopa({400, 400});
    ShyGuy shy({500, 500});
    InversePiranhaPlant inversePiranha({600, 600});
    Lakitu lakitu({100, 100});
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleLines(300, 300, 42, 58, RED);
        // DrawRectangleLines(400, 300, 48, 99, RED);

        // DrawRectangleLines(goomba.getBoundingBox().x, goomba.getBoundingBox().y, goomba.getBoundingBox().width,  goomba.getBoundingBox().height,BLUE);
        // goomba.test();
        // goomba.update(0.01f);
        // goomba.render();
        DrawRectangleLines(inversePiranha.getBoundingBox().x, inversePiranha.getBoundingBox().y, inversePiranha.getBoundingBox().width,  inversePiranha.getBoundingBox().height,BLUE);
        DrawRectangleLines(600, 600, 64, 132, RED);
        // goomba2.test();
        // goomba2.update(0.01f);
        // goomba2.render();
        goomba.update(0.01f);
        goomba.render();

        koopa.update(0.01f);
        koopa.render();
        if (IsKeyDown(KEY_SPACE)) {
            koopa.hit();
        }


        shy.update(0.01f);
        shy.render();

        piranha.update(0.01f);
        piranha.render();

        inversePiranha.update(0.01f);
        inversePiranha.render();

        lakitu.update(0.01f);
        lakitu.render();
        
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
