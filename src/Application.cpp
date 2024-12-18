#include "Application.hpp"

void Application::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        int currentState = menu.handle(); 

        if (currentState == 10) {
            game.start();  

        }
        else if (currentState == 11) {
            game = Game(menu.characterMenu(), menu.levelMenu());
            game.start();
        }
        menu.draw();
        EndDrawing();
    }

    CloseWindow();
}
