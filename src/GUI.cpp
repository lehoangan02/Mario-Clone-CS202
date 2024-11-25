#include "GUI.hpp"

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
    Button::draw();
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{241, 241, 29 ,255} : Color{70, 231, 193, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}

void SettingButton::draw(float radius) {
    Button::draw();
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{70, 231, 124 ,255} : Color{70, 231, 193, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}

void HighScoreButton::draw(float radius) {
    Button::draw();
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{255, 104, 170 ,255} : Color{70, 231, 193, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}

void InforButton::draw(float radius) {
    Button::draw();
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{255, 75, 78 ,255} : Color{70, 231, 193, 255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}


