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
        void draw(float radius = 15);
        int handle();
        bool getIsHovered() {return this->isHovered;}
        
        virtual ~Button() = default;
};



#endif /* GUI_h */
