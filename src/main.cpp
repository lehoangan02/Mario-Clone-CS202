#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>
#include <functional>
#include <stdint.h>

int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;


class ResourceManager {
private:
    static ResourceManager* instance;
    Font commonFont;

    ResourceManager() {
        commonFont = LoadFont("./assets/Font/InterBold.ttf");
    }

    ~ResourceManager() {
        UnloadFont(commonFont);
    }

public:
    static ResourceManager* GetInstance() {
        if (instance == nullptr) {
            instance = new ResourceManager();
        }
        return instance;
    }

    Font GetFont() {
        return commonFont;
    }
};

ResourceManager* ResourceManager::instance = nullptr;

class Button {
    protected:
        Rectangle outerRect;
        std::string content;
        Vector2 contentPos;
        Color contentColor;
        Font font;
        float fontSize;
        bool isHovered;
    public:
        Button(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font = ResourceManager::GetInstance()->GetFont());
        Button() : Button({0,0,0,0}, "", 0.0f, BLUE, 0) {}
        virtual void draw(float radius = 50);
        int handle();
        bool getIsHovered() {return this->isHovered;}
        int isClicked();

        virtual ~Button() = default;
};

class PlayButton : public Button {
public:
    PlayButton() = default;
    PlayButton(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font = ResourceManager::GetInstance()->GetFont()) : Button(rect, text, yText, textColor, fontSize) {}
    void draw(float radius = 50);
};

class SettingButton : public Button {
public:
    SettingButton() = default;
    SettingButton(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font = ResourceManager::GetInstance()->GetFont()) : Button(rect, text, yText, textColor, fontSize) {}

    void draw(float radius = 50);
};

class HighScoreButton : public Button {
public:
    HighScoreButton() = default;
    HighScoreButton(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font = ResourceManager::GetInstance()->GetFont()) : Button(rect, text, yText, textColor, fontSize) {}

    void draw(float radius = 50);
};

class InforButton : public Button {
public:
    InforButton() = default;
    InforButton(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font = ResourceManager::GetInstance()->GetFont()) : Button(rect, text, yText, textColor, fontSize) {}

    void draw(float radius = 50);
};

class CircleButton : public Button {
public:
    CircleButton() = default;
    CircleButton(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font = ResourceManager::GetInstance()->GetFont()) : Button(rect, text, yText, textColor, fontSize) {}

    void draw(float radius = 50);
};

Button::Button(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font) {
    this->outerRect = rect;
    this->content = text;
    this->font = font;
    this->fontSize = fontSize;
    this->contentColor = textColor;
    Vector2 textSize = MeasureTextEx(this->font, text.c_str(), this->fontSize,2);
    this->contentPos = {this->outerRect.x + (this->outerRect.width-textSize.x)/2, (yText == -1) ? (rect.y + (rect.height - textSize.y)/2) : yText};
    this->isHovered = false;
}

void Button::draw(float radius) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{241, 241, 29 ,255} : Color{3, 121, 255, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);

}

int Button::handle() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && this->isHovered) {
        this->isHovered = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 1;
    }
    return 0;
}

void PlayButton::draw(float radius) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{241, 241, 29 ,255} : Color{70, 231, 193, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}

void SettingButton::draw(float radius) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{241, 241, 29 ,255} : Color{70, 231, 124, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}

void HighScoreButton::draw(float radius) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{241, 241, 29 ,255} : Color{255, 104, 170, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}

void InforButton::draw(float radius) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{241, 241, 29 ,255} : Color{255, 75, 78, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}

void CircleButton::draw(float radius) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawCircle(outerRect.x + outerRect.width/2, outerRect.y + outerRect.height/2, outerRect.width/2, isHovered ? Color{241, 241, 29 ,255} : Color{3, 121, 255, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}

int main() {
    InitWindow(1024, 768, "Mario");
    Texture2D tex = LoadTexture("./assets/textures/GUI.png");
    
    PlayButton play({271, 595, 205, 59}, "Play", -1, WHITE, 26);
    SettingButton setting({547, 595, 205, 59 }, "Setting", -1, WHITE, 26);
    HighScoreButton highScore({271, 665, 205, 59}, "High Score", -1, WHITE, 26);
    InforButton infor({547, 665, 205, 59}, "Infor", -1, WHITE, 26);
    
    Texture2D textPlay = LoadTexture("./assets/textures/play.png");
    Texture2D textSetting = LoadTexture("./assets/textures/setting.png");
    Texture2D textHighScore = LoadTexture("./assets/textures/highScore.png");
    Texture2D textInfor = LoadTexture("./assets/textures/infor.png");
    
    int tab = 0;
    while(!WindowShouldClose()) {
        BeginDrawing();
        if (tab == 0) {
            ClearBackground(WHITE);
            DrawTexture(tex, 0, 0, RAYWHITE);
            play.draw();
            setting.draw();
            highScore.draw();
            infor.draw();
            
            if (play.handle()) tab = 1;
            else if (setting.handle()) tab = 2;
            else if (highScore.handle()) tab = 3;
            else if (infor.handle()) tab = 4;
        }
        else if (tab == 1) {
            ClearBackground(WHITE);
            DrawTexture(tex, 0, 0, RAYWHITE);
            play.draw();
            setting.draw();
            highScore.draw();
            infor.draw();
            
            DrawTexture(textPlay, 236, 235, WHITE);
            Button continu({441, 344, 141, 42}, "Continue", -1, WHITE, 22);
            Button newGame({441, 434, 141, 42}, "New Game", -1, WHITE, 22);
            Button quit({441, 514, 141, 42}, "Quit", -1, WHITE, 22);
            
            continu.draw();
            newGame.draw();
            quit.draw();
            
            if(quit.handle()) tab = 0;
            
            if (play.handle()) tab = 1;
            else if (setting.handle()) tab = 2;
            else if (highScore.handle()) tab = 3;
            else if (infor.handle()) tab = 4;

        }
        else if (tab == 2) {
            ClearBackground(WHITE);
            DrawTexture(tex, 0, 0, RAYWHITE);
            play.draw();
            setting.draw();
            highScore.draw();
            infor.draw();
            
            DrawTexture(textSetting, 236, 235, WHITE);
            Button mario({420, 280, 141, 42}, "Mario", -1, WHITE, 22);
            Button luigi({618, 280, 141, 42}, "Luigi", -1, WHITE, 22);
            CircleButton level1({447.5, 383, 50, 50}, "1", -1, WHITE, 22);
            CircleButton level2({560, 383, 50, 50}, "2", -1, WHITE, 22);
            CircleButton level3({669, 383, 50, 50}, "1", -1, WHITE, 22);
            Button save({326, 502, 141, 42}, "Save", -1, WHITE, 22);
            Button quit({560, 502, 141, 42}, "Quit", -1, WHITE, 22);
            
            mario.draw();
            luigi.draw();
            level1.draw();
            level2.draw();
            level3.draw();
            save.draw();
            quit.draw();
            
            if (save.handle() || quit.handle()) tab = 0;
            
            
            
            if (play.handle()) tab = 1;
            else if (setting.handle()) tab = 2;
            else if (highScore.handle()) tab = 3;
            else if (infor.handle()) tab = 4;

        }
        else if (tab == 3) {
            ClearBackground(WHITE);
            DrawTexture(tex, 0, 0, RAYWHITE);
            play.draw();
            setting.draw();
            highScore.draw();
            infor.draw();
            
            DrawTexture(textHighScore, 236, 235, WHITE);
            
            Button quit({247, 253, 141, 42}, "Quit", -1, WHITE, 22);
            quit.draw();
            if (quit.handle()) tab = 0;
            
            if (play.handle()) tab = 1;
            else if (setting.handle()) tab = 2;
            else if (highScore.handle()) tab = 3;
            else if (infor.handle()) tab = 4;

        }
        else if (tab == 4) {
            ClearBackground(WHITE);
            DrawTexture(tex, 0, 0, RAYWHITE);
            play.draw();
            setting.draw();
            highScore.draw();
            infor.draw();
            
            DrawTexture(textInfor, 236, 235, WHITE);
            Button quit({247, 253, 141, 42}, "Quit", -1, WHITE, 22);
            quit.draw();
            if (quit.handle()) tab = 0;

            
            
            if (play.handle()) tab = 1;
            else if (setting.handle()) tab = 2;
            else if (highScore.handle()) tab = 3;
            else if (infor.handle()) tab = 4;

        }
        EndDrawing();
    }
    CloseWindow();
}

