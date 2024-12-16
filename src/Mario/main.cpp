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
    
    Goomba goomba({300, 300}, {60, 60}, {10,0});
    goomba.setBound(100, 500, 100, 500);
    //ShyGuy shy({300, 300}, {42, 58}, {10,0}, 100, 700, 600, 900);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleLines(300, 300, 42, 58, RED);
        // DrawRectangleLines(400, 300, 48, 99, RED);

        // DrawRectangleLines(goomba.getBoundingBox().x, goomba.getBoundingBox().y, goomba.getBoundingBox().width,  goomba.getBoundingBox().height,BLUE);
        // goomba.test();
        goomba.update(0.01f);
        goomba.render();
        // DrawRectangleLines(goomba2.getBoundingBox().x, goomba2.getBoundingBox().y, goomba2.getBoundingBox().width,  goomba2.getBoundingBox().height,BLUE);

        // goomba2.test();
        // goomba2.update(0.01f);
        // goomba2.render();
        //DrawLineEx({700,100}, {700,400}, 2.0f, RED);
        //shy.update(0.01f);
        //shy.render();
        EndDrawing();
        
    }
    CloseWindow();
}