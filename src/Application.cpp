#include "Application.hpp"

Menu::Menu() {
    this->play = PlayButton({331, 718, 243, 71}, "Play", -1, BLACK, 32, FONT);
    this->setting = SettingButton({655, 718, 243, 71 }, "Setting", -1, BLACK, 32);
    this->highScore = HighScoreButton({331, 799, 243, 71}, "High Score", -1, BLACK, 32);
    this->infor = InforButton({655, 799, 243, 71}, "Infor", -1, BLACK, 32);
}


void Menu::draw() {
    Texture2D texture = LoadTexture(".assets/Font");
    DrawTexture(texture, 0, 0, WHITE);
    play.draw();
    setting.draw();
    highScore.draw();
    infor.draw();
}

void Menu::hanlde() {
    play.handle();
    setting.handle();
    highScore.handle();
    infor.handle();
}

int8_t Menu::clicked() {
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if(play.getIsHovered()) return 1;
        if(setting.getIsHovered()) return 2;
        if(highScore.getIsHovered()) return 3;
        if(infor.getIsHovered()) return 4;
    }
    return 0;
}



void Application::run() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario");
    SetTextureFilter(FONT.texture, TEXTURE_FILTER_POINT);
    SetTargetFPS(60);
    while (!WindowShouldClose() && this->tab != -1) {
        switch (this->tab) {
            case 0:
                this->tab = menu();
                break;
            case 1:
                //
            default:
                this->tab = -1;
                break;
        }
        
    }
    CloseWindow();
}


int Application::menu() {
    Menu menu;
    int8_t flag = -1;
    do {
        menu.hanlde();
        BeginDrawing();
            ClearBackground(WHITE);
            menu.draw();
            flag = menu.clicked();
        EndDrawing();
    } while (!WindowShouldClose() && !flag);
    return flag;
}

int main() {
    Application app;
    app.run();
}
