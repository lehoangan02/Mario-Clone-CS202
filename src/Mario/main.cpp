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
    InversePiranhaPlant goomba({300, 300}, {48, 99} , {0, 10}); //size should be scale of 32x66
    PiranhaPlant goomba2({400, 300}, {48, 99} , {0, 10}); //size should be scale of 32x66
    //Texture2D texture = LoadTexture("./assets/textures/PiranhaPlant_1.png");
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleLines(300, 300, 48, 99, RED);
        DrawRectangleLines(400, 300, 48, 99, RED);
        
        goomba.test();
        goomba.update(0.01f);
        goomba.render();


        goomba2.test();
        goomba2.update(0.01f);
        goomba2.render();
        //DrawTexture(LoadTexture("./assets/textures/PiranhaPlant_0.png"), 300, 300, WHITE);
        //DrawTexturePro(texture, {0,0,32,66}, {300, 300, 32, 66}, {32, 66}, 180.0f, WHITE);
        EndDrawing();
    }
    CloseWindow();
}