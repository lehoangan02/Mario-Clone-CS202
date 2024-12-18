#ifndef GUI_hpp
#define GUI_hpp

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

#include "ResourceManager.hpp"
#include "raylib.h"
#include <string>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

class Button {
protected:
    Rectangle outerRect;
    std::string content;
    Vector2 contentPos;
    Color contentColor;
    Font font;
    float fontSize;
    bool isHovered;
    Color defaultColor;
    Color hoverColor;
    bool isChoose;

public:
    Button(Rectangle rect, Color defaultColor ,const std::string& text, Color textColor, float fontSize, Font font, bool isChoose);
    Button() = default;
    virtual void draw(float radius = 50);

    bool isClicked();

    bool getChoose() const;

    void setChoose(bool newChoose);
};

class QuitButton : public Button {
private:
    Texture2D texture;
public:
    QuitButton() = default;
    QuitButton(Rectangle rect);
    void draw();
};

class Menu {
private:
    Texture2D pageTexture;
    
    Button playButton;
    Button settingButton;
    Button highScoreButton;
    Button inforButton;

    Texture2D playTexture;
    Button continueButton;
    Button newGameButton;

    Texture2D settingTexture;
    Button characterButton;
    Button soundButton;

    Texture2D characterTexture;
    Button characterButtons[2];

    Texture2D soundTexture;
    Button soundButtons[2];

    Texture2D highScoreTexture;
    QuitButton quitButton;

    Texture2D inforTexture;
    int type;

public:
    Menu();
    void draw();
    int characterMenu();
    int soundMenu();

    int handle();
};


#endif // GUI_HPP
