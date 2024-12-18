#include "GUI.hpp"

Button::Button(Rectangle rect, Color defaultColor, const std::string& text, Color textColor, float fontSize, Font font, bool isChoose) : outerRect(rect), defaultColor(defaultColor),content(text), contentColor(textColor), fontSize(fontSize), font(font), isHovered(false), isChoose(isChoose), hoverColor(Color{198, 198, 35, 255}){
    
    Vector2 textSize = MeasureTextEx(this->font, text.c_str(), this->fontSize,2);
    this->contentPos = {this->outerRect.x + (this->outerRect.width-textSize.x)/2,  (rect.y + (rect.height - textSize.y)/2)};
}

void Button::draw(float radius) {
    Color tmpColor = isChoose ? Color{218, 40, 90, 255} : defaultColor;
    
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? hoverColor : tmpColor);
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);

}

bool Button::isClicked() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && this->isHovered) {
        this->isHovered = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 1;
    }
    return 0;
}

bool Button::getChoose() const {
    return isChoose;
}

void Button::setChoose(bool newChoose) {
    isChoose = newChoose;
}

void CircleButton::draw() {
    Color tempColor = isChoose ? Color{218, 40, 90, 255} : Color{3, 121, 255, 255};
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawCircle(outerRect.x + outerRect.width/2, outerRect.y + outerRect.height/2, outerRect.width/2, isHovered ? Color{241, 241, 29 ,255} : tempColor);
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, {0,0}, 0, this->fontSize, 2, this->contentColor);
}

Menu::Menu() {
    this->pageTexture = ResourceManager::GetInstance()->GetTexture("pageTexture");
    
    playButton = Button({271, 595, 205, 59}, Color{70, 231, 193, 255} ,"Play", WHITE, 26, ResourceManager::GetInstance()->GetFont(), 0);
    settingButton = Button({547, 595, 205, 59 }, Color{70, 231, 124, 255} ,"Setting", WHITE, 26, ResourceManager::GetInstance()->GetFont(), 0);
    highScoreButton = Button({271, 665, 205, 59}, Color{255, 104, 170, 255} ,"High Score", WHITE, 26,
        ResourceManager::GetInstance()->GetFont(), 0);
    inforButton = Button({547, 665, 205, 59}, Color{255, 75, 78, 255},"Infor", WHITE, 26, ResourceManager::GetInstance()->GetFont(), 0);
    
    this->playTexture = ResourceManager::GetInstance()->GetTexture("playTexture");
    this->settingTexture = ResourceManager::GetInstance()->GetTexture("settingTexture");
    this->highScoreTexture = ResourceManager::GetInstance()->GetTexture("highScoreTexture");
    this->inforTexture = ResourceManager::GetInstance()->GetTexture("inforTexture");
    
    continueButton = Button({441, 344, 141, 42}, Color{3, 121, 255, 255} ,"Continue", WHITE, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    newGameButton = Button({441, 434, 141, 42}, Color{3, 121, 255, 255},"New Game", WHITE, 22, ResourceManager::GetInstance()->GetFont(), 0);
    quit1Button = Button({441, 514, 141, 42}, Color{3, 121, 255, 255},"Quit", WHITE, 22, ResourceManager::GetInstance()->GetFont(), 0);
    
    characterButton[0] = Button({420, 280, 141, 42}, Color{3, 121, 255, 255},"Mario", WHITE, 22, ResourceManager::GetInstance()->GetFont(), 1);
    characterButton[1] = Button({618, 280, 141, 42}, Color{3, 121, 255, 255},"Luigi", WHITE, 22,
        ResourceManager::GetInstance()->GetFont(), 0);

    levelButton[0] = CircleButton({447.5, 383, 50, 50}, Color{3, 121, 255, 255},"1", WHITE, 22,
        ResourceManager::GetInstance()->GetFont(), 1);
    levelButton[1] = CircleButton({560, 383, 50, 50}, Color{3, 121, 255, 255},"2", WHITE, 22, ResourceManager::GetInstance()->GetFont(), 0);
    levelButton[2] = CircleButton({669, 383, 50, 50}, Color{3, 121, 255, 255},"3", WHITE, 22, ResourceManager::GetInstance()->GetFont(), 0);
    
    quit2Button = Button({560, 502, 141, 42}, Color{3, 121, 255, 255},"Quit", WHITE, 22, ResourceManager::GetInstance()->GetFont(), 0);
    
    quitButton = Button({247, 253, 141, 42}, Color{3, 121, 255, 255}, "Quit", WHITE, 22, ResourceManager::GetInstance()->GetFont(), 0);
    type = 0;
}

void Menu::draw(){
    DrawTextureEx(pageTexture, {0, 0}, 0, 0.125, WHITE);
    playButton.draw();
    settingButton.draw();
    highScoreButton.draw();
    inforButton.draw();
    
    if (type == 1) {
        DrawTextureEx(playTexture, {236, 235}, 0, 0.125, WHITE);
        continueButton.draw();
        newGameButton.draw();
        quit1Button.draw();
    }
    else if (type == 2 || type == 5 || type == 6 || type == 7 || type == 8 || type == 9) {
        DrawTextureEx(settingTexture, {236, 235}, 0, 0.125, WHITE);
        levelButton[0].draw();
        levelButton[1].draw();
        levelButton[2].draw();
        
        characterButton[0].draw();
        characterButton[1].draw();
        quit2Button.draw();
    }
    else if (type == 3) {
        DrawTextureEx(highScoreTexture, {236, 235}, 0, 0.125, WHITE);
        quitButton.draw();
    }
    else if (type == 4) {
        DrawTextureEx(inforTexture, {236, 235}, 0, 0.125, WHITE);
        quitButton.draw();
    }
}

int Menu::handle() {
    if (playButton.isClicked()) type = 1;
    else if (settingButton.isClicked()) type = 2;
    else if (highScoreButton.isClicked()) type = 3;
    else if (inforButton.isClicked()) type = 4;
    
    if (quitButton.isClicked() || quit1Button.isClicked() || quit2Button.isClicked()) {
        type = 0;
    }
    else if (newGameButton.isClicked()) {
        type = 10;
    }
    else if (continueButton.isClicked()) {
        type = 11;
    }
    else if (characterButton[0].isClicked() && !characterButton[0].getChoose()) {
        characterButton[0].setChoose(true);
        characterButton[1].setChoose(false);
        type = 5;
    }
    else if (characterButton[1].isClicked() && !characterButton[1].getChoose()) {
        characterButton[1].setChoose(true);
        characterButton[0].setChoose(false);
        type = 6;
    }
    else if (levelButton[0].isClicked() && !levelButton[0].getChoose()) {
        levelButton[0].setChoose(true);
        levelButton[1].setChoose(false);
        levelButton[2].setChoose(false);
        type = 7;
    }
    else if (levelButton[1].isClicked() && !levelButton[1].getChoose()) {
        levelButton[0].setChoose(false);
        levelButton[1].setChoose(true);
        levelButton[2].setChoose(false);
        type = 8;
    }
    else if (levelButton[2].isClicked() && !levelButton[2].getChoose()) {
        levelButton[0].setChoose(false);
        levelButton[1].setChoose(false);
        levelButton[2].setChoose(true);
        type = 9;
    }
    return type;
}

int Menu::characterMenu() {
    if (characterButton[0].getChoose()) return 0;
    else return 1;
}

int Menu::levelMenu() {
    if (levelButton[0].getChoose()) return 0;
    else if (levelButton[0].getChoose()) return 1;
    else return 2;
}