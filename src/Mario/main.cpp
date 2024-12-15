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
    PiranhaPlant goomba({ 400, 600 });
    goomba.setHeightInGround(0);
    goomba.setBound(0, 0, 666, 600);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        goomba.test();
        goomba.update(0.01f);
        goomba.render();
        EndDrawing();
    }
    CloseWindow();
}