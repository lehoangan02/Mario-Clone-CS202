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
    Goomba goomba(Vector2{600, 400}, {40,40}, {30,0});
    
    // KoopaTroopa goomba(Vector2{600, 400});
    goomba.setBound(0, 1024, 0, 768);
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