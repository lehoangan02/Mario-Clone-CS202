#include "../Application.hpp"

int main() {

	
    SetTargetFPS(60);
    InitAudioDevice();
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 768, "Game Window");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    ResourceManager::GetInstance()->LoadResources();
    Application app;
    app.run();
    CloseAudioDevice();
}

// #include "../characters/Enemy.hpp"
// #include "raylib.h"
// #include <thread>

// int main() {
//     SetConfigFlags(FLAG_MSAA_4X_HINT);
//     InitWindow(1024, 768, "Game Window");
//     SetWindowState(FLAG_WINDOW_RESIZABLE);
//     SetTargetFPS(60);
    
//     KoopaTroopa koopa({300, 300});
    
//     while(!WindowShouldClose()) {
//         BeginDrawing();
//         ClearBackground(BLACK);
//         DrawRectangleLines(300, 300, 42, 58, RED);
//         // DrawRectangleLines(400, 300, 48, 99, RED);

//         // DrawRectangleLines(goomba.getBoundingBox().x, goomba.getBoundingBox().y, goomba.getBoundingBox().width,  goomba.getBoundingBox().height,BLUE);
//         // goomba.test();
//         // goomba.update(0.01f);
//         // goomba.render();
//         // DrawRectangleLines(goomba2.getBoundingBox().x, goomba2.getBoundingBox().y, goomba2.getBoundingBox().width,  goomba2.getBoundingBox().height,BLUE);

//         // goomba2.test();
//         // goomba2.update(0.01f);
//         // goomba2.render();
//         DrawLineEx({700,100}, {700,400}, 2.0f, RED);
//         koopa.update(0.01f);
//         koopa.render();
//         if (IsKeyPressed(KEY_SPACE)) {
//             std::this_thread::sleep_for(std::chrono::milliseconds(100));
//             koopa.hit();
//         }
//         // shy.update(0.01f);
//         // shy.render();
//         EndDrawing();
        
//     }
//     CloseWindow();
// }

// // #include "../Application.hpp"


// // #include "../levels/Level.hpp"
// // int main() {
// //     const int screenWidth = 1024;
// //     const int screenHeight = 896;

// //     InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

// //     SetTargetFPS(60);
// //     LevelFactory& factory = LevelFactory::GetLevelFactory();
// //     Level* level = factory.CreateLevel(LevelFactory::LEVEL_101);

// //     while (!WindowShouldClose()) {

// //         BeginDrawing();
// //         ClearBackground(RAYWHITE);

// //         if(IsKeyPressed(KEY_P)) {
// //             level = factory.CreateLevel(LevelFactory::LEVEL_103);
// //         }
// //         level->update(GetFrameTime());

// //         level->render();
// //         EndDrawing();
// //     }

// //     CloseWindow();
// // }

