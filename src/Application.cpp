#include "Application.hpp"

void Application::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        int currentState = menu.handle(); 

        if (currentState == 10) {
            game.start();  
        }

        menu.draw();  

        EndDrawing();
    }

    CloseWindow();
}
