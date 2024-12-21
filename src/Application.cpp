#include "Application.hpp"


void Application::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
            
        if (tab >= 0 && tab < 10) {
            menu.draw();
            tab = menu.handle();
            if(menu.getIsChange()) {
                menu.setIsChange(false);
                game = Game(menu.characterMenu(), menu.levelMenu());
            }
        } 
        else  if (tab == 10){
            game.start();
            if (game.getState() == LEVEL_RETURN_MESSAGE::QUIT) {
                tab = 0;
            }
        }
        else if (tab == 11) {
            game.start();
            if (game.getState() == LEVEL_RETURN_MESSAGE::QUIT) {
                tab = 0;
            }
        }
        EndDrawing();
    }

    CloseWindow();
}
