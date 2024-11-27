#include "Application.hpp"

void Application::run() {
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        
        menu.draw();
        menu.handle();
        EndDrawing();
    }
    CloseWindow();
}
