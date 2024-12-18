#include "Application.hpp"

void Application::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
            
            menu.draw();
            tab = menu.handle();
        EndDrawing();
    }

    CloseWindow();
}
