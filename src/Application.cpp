#include "Application.hpp"


// void Application::run() {
//     while (!WindowShouldClose() && this->tab != -1) {
//         switch (this->tab) {
//             case 0:
//                 this->tab = menuApp();
//                 break;
//             case 10:
//                 this->tab = gameApp();
//                 break;
//             case 11:
//                 this->tab = gameApp();
//                 break;
//             default:
//                 break;
//         }
//     }
//     CloseWindow();
// }


// int Application::gameApp() {
//     game = Game(menu.characterMenu(), menu.levelMenu());

//     while (!WindowShouldClose) {
//         if (game.getState() == LEVEL_RETURN_MESSAGE::QUIT) {
//             return 0;
//         }
//         BeginDrawing();
//         ClearBackground(WHITE);
//         game.start();
//         EndDrawing();
//     } 
//     return -1;
// }

// int Application::menuApp() {
//     menu = Menu();
//     do{
//         if (tab == 10) {
//             game = Game(menu.characterMenu(), menu.levelMenu());
//             return 10;
//         }
//         else if (tab == 11) {
//             game = Game(menu.characterMenu(), menu.levelMenu());
//             return 11;
//         }
//         BeginDrawing();
//         ClearBackground(WHITE);
//         menu.draw();
//         tab = menu.handle();
//         EndDrawing();
//     } while (!WindowShouldClose);
//     return -1;
// }

void Application::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (tab >= 0 && tab < 10) {
            menu.draw();
            tab = menu.handle();
            if (menu.getIsChange()) {
                menu.setIsChange(false);
                game = Game(menu.characterMenu(), menu.levelMenu());
            }
            if (menu.handle() == 11) {
                game.change("continue.txt");
                tab = 11;
            }
        }
        else if (tab == 10) {
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