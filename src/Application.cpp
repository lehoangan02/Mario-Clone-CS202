#include "Application.hpp"

void Application::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
            
        if (tab >= 0 && tab < 10) {
            menu.draw();
            tab = menu.handle();
        } 
        else  if (tab == 10){
            game.start();
        }
        else if (tab == 11) {
            game.start();
        }
        EndDrawing();
    }

    CloseWindow();
}
