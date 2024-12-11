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
    Goomba goomba(Vector2{100, 100}, 100);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        goomba.Update(0.1f);
        goomba.render();
        EndDrawing();
    }
    CloseWindow();
}