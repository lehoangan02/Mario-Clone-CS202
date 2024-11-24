#ifndef GUI_h
#define GUI_h

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


Font FONT = LoadFont(<#const char *fileName#>)
    
};

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
        Button(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font = FONT);
        Button() : Button({0,0,0,0}, "", 0.0f, BLUE, 0) {}
        virtual void draw(float radius = 15);
        int handle();
        bool getIsHovered() {return this->isHovered;}
        
        virtual ~Button() = default;
};

class PlayButton : public Button {
public:
    void draw(float radius = 15);
};

class SettingButton : public Button {
public:
    void draw(float radius = 15);
};

class HighScoreButton : public Button {
public:
    void draw(float radius = 15);
};

class InforButton : public Button {
public:
    void draw(float radius = 15);
};

#endif /* GUI_h */
