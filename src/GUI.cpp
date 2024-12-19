#include "GUI.hpp"

Button::Button(Rectangle rect, Color defaultColor, const std::string& text, Color textColor, float fontSize, Font font, bool isChoose) : outerRect(rect), defaultColor(defaultColor),content(text), contentColor(textColor), fontSize(fontSize), font(font), isHovered(false), isChoose(isChoose), hoverColor(Color{251, 158, 198, 255}){
    
    Vector2 textSize = MeasureTextEx(this->font, text.c_str(), this->fontSize,2);
    this->contentPos = {this->outerRect.x + (this->outerRect.width-textSize.x)/2,  (rect.y + (rect.height - textSize.y)/2)};
}

void Button::draw(float radius) {
    Color tmpColor = isChoose ? Color{255, 206, 12, 255} : defaultColor;
    
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    if (isChoose) this->isHovered = false;
    DrawRectangleRounded({outerRect.x + 1.7f, outerRect.y + 1.7f, outerRect.width, outerRect.height}, radius/55, 32, Fade(BLACK, 0.7f));
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

QuitButton::QuitButton(Rectangle rect) {
    this->texture = ResourceManager::GetInstance()->GetTexture("quitTexture");
    this->outerRect = rect;
}

void QuitButton::draw() {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawTextureEx(this->texture, {this->outerRect.x, this->outerRect.y}, 0.0f, this->isHovered ? 0.135 : 0.125 , BLACK);
}

Menu::Menu() {
    this->pageTexture = ResourceManager::GetInstance()->GetTexture("pageTexture");
    
    playButton = Button({177, 560, 205, 59}, Color{240, 193, 225, 255} ,"Play", BLACK, 26, ResourceManager::GetInstance()->GetFont(), 0);
    settingButton = Button({662, 560, 205, 59 }, Color{240, 193, 225, 255} ,"Setting", BLACK, 26, ResourceManager::GetInstance()->GetFont(), 0);
    highScoreButton = Button({177, 659, 205, 59}, Color{240, 193, 225, 255} ,"High Score", BLACK, 26,
        ResourceManager::GetInstance()->GetFont(), 0);
    inforButton = Button({662, 659, 205, 59}, Color{240, 193, 225, 255},"Info", BLACK, 26, ResourceManager::GetInstance()->GetFont(), 0);
    
    this->playTexture = ResourceManager::GetInstance()->GetTexture("playTexture");
    this->settingTexture = ResourceManager::GetInstance()->GetTexture("settingTexture");
    this->characterTexture = ResourceManager::GetInstance()->GetTexture("settingCharacter");
    this->soundTexture = ResourceManager::GetInstance()->GetTexture("settingSound");
    this->highScoreTexture = ResourceManager::GetInstance()->GetTexture("highScoreTexture");
    this->inforTexture = ResourceManager::GetInstance()->GetTexture("inforTexture");
 
    continueButton = Button({441, 290, 141, 42}, Color{240, 193, 225, 255} ,"Continue", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    newGameButton = Button({441, 363, 141, 42}, Color{240, 193, 225, 255},"New Game", BLACK, 22, ResourceManager::GetInstance()->GetFont(), 0);

    characterButton = Button({441, 239, 141, 42}, Color{240, 193, 225, 255} ,"Character", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    soundButton = Button({441, 316, 141, 42}, Color{240, 193, 225, 255} ,"Sound", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);

    characterButtons[0] = Button({288, 422, 141, 42}, Color{240, 193, 225, 255} ,"Mario", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    characterButtons[1] = Button({582, 422, 141, 42}, Color{240, 193, 225, 255} ,"Luigi", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    
    soundButtons[0] = Button({441, 258, 141, 42}, Color{240, 193, 225, 255} ,"Yes", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    soundButtons[1] = Button({441, 332, 141, 42}, Color{240, 193, 225, 255} ,"No", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);

    quitButton = QuitButton(Rectangle{256, 189, 30, 30});
    type = 0;
}



void Menu::draw(){
    DrawTextureEx(pageTexture, {0, 0}, 0, 0.125, WHITE);
    if (type == 0) {
        playButton.draw();
        settingButton.draw();
        highScoreButton.draw();
        inforButton.draw();
    }
    
    if (type == 1) {
        DrawTextureEx(playTexture, {236, 167}, 0, 0.125, WHITE);
        continueButton.draw();
        newGameButton.draw();
        quitButton.draw();
    }
    else if (type == 2) {
        DrawTextureEx(settingTexture, {236, 167}, 0, 0.125, WHITE);
        characterButton.draw();
        soundButton.draw();
        quitButton.draw();
    }
    else if (type == 3) {
        DrawTextureEx(characterTexture, {236, 167}, 0, 0.125, WHITE);
        characterButtons[0].draw();
        characterButtons[1].draw();
        quitButton.draw();
    }
    else if (type == 4) {
        DrawTextureEx(soundTexture, {236, 167}, 0, 0.125, WHITE);
        soundButtons[0].draw();
        soundButtons[1].draw();
        quitButton.draw();
    }
    else if (type == 5) {
        DrawTextureEx(highScoreTexture, {236, 167}, 0, 0.125, WHITE);
        quitButton.draw();
    }
    else if (type == 6) {
        DrawTextureEx(inforTexture, {236, 167}, 0, 0.125, WHITE);
        quitButton.draw();
    }
}

int Menu::handle() {
    if (playButton.isClicked()) type = 1;
    else if (settingButton.isClicked()) type = 2;
    else if (highScoreButton.isClicked()) type = 5;
    else if (inforButton.isClicked()) type = 6;
    
    if (quitButton.isClicked()) {
        type = 0;
    }
    else if (newGameButton.isClicked()) {
        type = 10;
    }
    else if (continueButton.isClicked()) {
        type = 11;
    }
    else if (characterButton.isClicked()) {
        type = 3;
    }
    else if (soundButton.isClicked()) {
        type = 4;
    }
    else if (characterButtons[0].isClicked() && !characterButtons[0].getChoose()) {
        characterButtons[0].setChoose(true);
        characterButtons[1].setChoose(false);
        type = 3;
    }
    else if (characterButtons[1].isClicked() && !characterButtons[1].getChoose()) {
        characterButtons[1].setChoose(true);
        characterButtons[0].setChoose(false);
        type = 3;
    }
    else if (soundButtons[0].isClicked() && !soundButtons[0].getChoose()) {
        soundButtons[0].setChoose(true);
        soundButtons[1].setChoose(false);
        type = 4;
    }
    else if (soundButtons[1].isClicked() && !soundButtons[1].getChoose()) {
        soundButtons[1].setChoose(true);
        soundButtons[0].setChoose(false);
        type = 4;
    }
    return type;
}

int Menu::characterMenu() {
    if (characterButtons[0].getChoose()) return 0;
    else return 1;
}

int Menu::soundMenu() {
    if (soundButtons[0].getChoose()) return 0;
    else return 1;
}

