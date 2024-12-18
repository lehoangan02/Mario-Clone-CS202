#include "Application.hpp"

void Application::run() {
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (tab = 0) {
            menu.draw();
            tab = menu.handle();
        }
        else {
            game.start();
        }
        EndDrawing();
    }

    CloseWindow();
}
