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

QuitButton::QuitButton(Rectangle rect, Texture2D texture) {
    this->texture = texture;
    this->outerRect = rect;
}
void QuitButton::draw(float radius) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawTextureEx(this->texture, {this->outerRect.x, this->outerRect.y}, 0.0f, this->isHovered ? 0.125f : 0.11f , BLACK);
}

void QuitButton::draw(Color alpha) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawTextureEx(this->texture, {this->outerRect.x, this->outerRect.y}, 0.0f, this->isHovered ? 0.125f : 0.11f, alpha);
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
    this->mapTexture = ResourceManager::GetInstance()->GetTexture("settingMap");
    //this->levelTexture = ResourceManager::GetInstance()->GetTexture("settingLevel");
    this->highScoreTexture = ResourceManager::GetInstance()->GetTexture("highScoreTexture");
    this->inforTexture = ResourceManager::GetInstance()->GetTexture("inforTexture");
 
    continueButton = Button({450, 281, 141, 42}, Color{240, 193, 225, 255} ,"Continue", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    newGameButton = Button({450, 342, 141, 42}, Color{240, 193, 225, 255},"New Game", BLACK, 22, ResourceManager::GetInstance()->GetFont(), 0);
    selectedButton = Button({450, 403, 141, 42}, Color{240, 193, 225, 255} ,"Selected", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);

    characterButton = Button({450, 248, 141, 42}, Color{240, 193, 225, 255} ,"Character", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    mapButton = Button({450, 314, 141, 42}, Color{240, 193, 225, 255} ,"Level", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    // levelButton = Button({450, 380, 141, 42}, Color{240, 193, 225, 255} ,"Level", BLACK, 22,
    //     ResourceManager::GetInstance()->GetFont(), 0);

    characterButtons[0] = Button({305, 422, 141, 42}, Color{240, 193, 225, 255} ,"Mario", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 1);
    characterButtons[1] = Button({575, 422, 141, 42}, Color{240, 193, 225, 255} ,"Luigi", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    
    mapButtons[0] = Button({275.5, 251, 136, 101}, Color{240, 193, 225, 255} ,"Map 1", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 1);
    mapButtons[1] = Button({444, 251, 136, 101}, Color{240, 193, 225, 255} ,"Map 2", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    mapButtons[2] = Button({613, 251, 136, 101}, Color{240, 193, 225, 255} ,"Map 3", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    mapButtons[3] = Button({275.5, 384, 136, 101}, Color{240, 193, 225, 255} ,"Hidden 1", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    mapButtons[4] = Button({444, 384, 136, 101}, Color{240, 193, 225, 255} ,"Hidden 2", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    mapButtons[5] = Button({613, 384, 136, 101}, Color{240, 193, 225, 255} ,"Custom", BLACK, 22,
        ResourceManager::GetInstance()->GetFont(), 0);
    
    // levelButtons[0] = Button({450, 251, 141, 42}, Color{240, 193, 225, 255} ,"Easy", BLACK, 22,
    //     ResourceManager::GetInstance()->GetFont(), 0);
    // levelButtons[1] = Button({450, 316, 141, 42}, Color{240, 193, 225, 255} ,"Medium", BLACK, 22,
    //     ResourceManager::GetInstance()->GetFont(), 0);
    // levelButtons[2] = Button({450, 384, 141, 42}, Color{240, 193, 225, 255} ,"Hard", BLACK, 22,
    //     ResourceManager::GetInstance()->GetFont(), 0);

    quitButton = QuitButton(Rectangle{255, 183, 24, 24});
    isChange = false;
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
        selectedButton.draw();
        quitButton.draw();
    }
    else if (type == 2) {
        DrawTextureEx(settingTexture, {236, 167}, 0, 0.125, WHITE);
        characterButton.draw();
        mapButton.draw();
        //levelButton.draw();
        quitButton.draw();
    }
    else if (type == 3) {
        DrawTextureEx(characterTexture, {236, 167}, 0, 0.125, WHITE);
        characterButtons[0].draw();
        characterButtons[1].draw();
        quitButton.draw();
    }
    else if (type == 4) {
        DrawTextureEx(mapTexture, {236, 167}, 0, 0.125, WHITE);
        mapButtons[0].draw();
        mapButtons[1].draw();
        mapButtons[2].draw();
        mapButtons[3].draw();
        mapButtons[4].draw();
        mapButtons[5].draw();
        quitButton.draw();
    }
    // else if (type == 5) {
    //     DrawTextureEx(levelTexture, {236, 167}, 0, 0.125, WHITE);
    //     levelButtons[0].draw();
    //     levelButtons[1].draw();
    //     levelButtons[2].draw();
    //     quitButton.draw();
    // }
    else if (type == 6) {
        DrawTextureEx(highScoreTexture, {236, 167}, 0, 0.125, WHITE);
        std::string score1Text = std::to_string(score[0]);
        std::string score2Text = std::to_string(score[1]);
        std::string score3Text = std::to_string(score[2]);

        Vector2 score1Size = MeasureTextEx(ResourceManager::GetInstance()->GetFont(), score1Text.c_str(), 22, 2);
        Vector2 score2Size = MeasureTextEx(ResourceManager::GetInstance()->GetFont(), score2Text.c_str(), 22, 2);
        Vector2 score3Size = MeasureTextEx(ResourceManager::GetInstance()->GetFont(), score3Text.c_str(), 22, 2);

        DrawTextPro(ResourceManager::GetInstance()->GetFont(), score1Text.c_str(), {418 + (230 - score1Size.x) / 2, 267 + (48 - score1Size.y) / 2}, {0, 0}, 0, 22, 2, BLACK);
        DrawTextPro(ResourceManager::GetInstance()->GetFont(), score2Text.c_str(), {418 + (230 - score2Size.x) / 2, 343 + (48 - score2Size.y) / 2}, {0, 0}, 0, 22, 2, BLACK);
        DrawTextPro(ResourceManager::GetInstance()->GetFont(), score3Text.c_str(), {418 + (230 - score3Size.x) / 2, 419 + (48 - score3Size.y) / 2}, {0, 0}, 0, 22, 2, BLACK);
        quitButton.draw();
    }
    else if (type == 7) {
        DrawTextureEx(inforTexture, {236, 167}, 0, 0.125, WHITE);
        quitButton.draw();
    }
}

int Menu::handle() {
    if (playButton.isClicked()) type = 1;
    else if (settingButton.isClicked()) type = 2;
    else if (highScoreButton.isClicked()) {
        type = 6;
        getScore(score[0], score[1], score[2], "./score.txt");
    }
    else if (inforButton.isClicked()) type = 7;
    
    if (quitButton.isClicked()) {
        type = 0;
    }
    if (newGameButton.isClicked()) {
        type = 10;
    }
    else if (continueButton.isClicked()) {
        type = 11;
    }
    else if (selectedButton.isClicked()) {
        type = 12;
    }
    else if (characterButton.isClicked()) {
        type = 3;
    }
    else if (mapButton.isClicked()) {
        type = 4;
    }
    // else if (levelButton.isClicked()) {
    //     type = 5;
    // }
    else if (characterButtons[0].isClicked() && !characterButtons[0].getChoose()) {
        characterButtons[0].setChoose(true);
        characterButtons[1].setChoose(false);
        type = 3;
        isChange = true;
    }
    else if (characterButtons[1].isClicked() && !characterButtons[1].getChoose()) {
        characterButtons[1].setChoose(true);
        characterButtons[0].setChoose(false);
        type = 3;
        isChange = true;
    }
    else if (mapButtons[0].isClicked() && !mapButtons[0].getChoose()) {
        mapButtons[0].setChoose(true);
        mapButtons[1].setChoose(false);
        mapButtons[2].setChoose(false);
        mapButtons[3].setChoose(false);
        mapButtons[4].setChoose(false);
        mapButtons[5].setChoose(false);
        type = 4;
        isChange = true;
    }
    else if (mapButtons[1].isClicked() && !mapButtons[1].getChoose()) {
        mapButtons[1].setChoose(true);
        mapButtons[0].setChoose(false);
        mapButtons[2].setChoose(false);
        mapButtons[3].setChoose(false);
        mapButtons[4].setChoose(false);
        mapButtons[5].setChoose(false);
        type = 4;
        isChange = true;
    }
    else if (mapButtons[2].isClicked() && !mapButtons[2].getChoose()) {
        mapButtons[2].setChoose(true);
        mapButtons[1].setChoose(false);
        mapButtons[0].setChoose(false);
        mapButtons[3].setChoose(false);
        mapButtons[4].setChoose(false);
        mapButtons[5].setChoose(false);
        type = 4;
        isChange = true;
    }
    else if (mapButtons[3].isClicked() && !mapButtons[3].getChoose()) {
        mapButtons[3].setChoose(true);
        mapButtons[1].setChoose(false);
        mapButtons[2].setChoose(false);
        mapButtons[0].setChoose(false);
        mapButtons[4].setChoose(false);
        mapButtons[5].setChoose(false);
        type = 4;
        isChange = true;
    }
    else if (mapButtons[4].isClicked() && !mapButtons[4].getChoose()) {
        mapButtons[4].setChoose(true);
        mapButtons[1].setChoose(false);
        mapButtons[2].setChoose(false);
        mapButtons[3].setChoose(false);
        mapButtons[0].setChoose(false);
        mapButtons[5].setChoose(false);
        type = 4;
        isChange = true;
    }
    else if (mapButtons[5].isClicked() && !mapButtons[5].getChoose()) {
        mapButtons[5].setChoose(true);
        mapButtons[1].setChoose(false);
        mapButtons[2].setChoose(false);
        mapButtons[3].setChoose(false);
        mapButtons[4].setChoose(false);
        mapButtons[0].setChoose(false);
        type = 4;
        isChange = true;
    }
    // else if (levelButtons[0].isClicked() && !levelButtons[0].getChoose()) {
    //     levelButtons[0].setChoose(true);
    //     levelButtons[1].setChoose(false);
    //     levelButtons[2].setChoose(false);
    //     type = 5;
    //     isChange = true;
    // }
    // else if (levelButtons[1].isClicked() && !levelButtons[1].getChoose()) {
    //     levelButtons[1].setChoose(true);
    //     levelButtons[0].setChoose(false);
    //     levelButtons[2].setChoose(false);
    //     type = 5;
    //     isChange = true;
    // }
    // else if (levelButtons[2].isClicked() && !levelButtons[2].getChoose()) {
    //     levelButtons[2].setChoose(true);
    //     levelButtons[1].setChoose(false);
    //     levelButtons[0].setChoose(false);
    //     type = 5;
    //     isChange = true;
    // }
    return type;
}

int Menu::characterMenu() {
    if (characterButtons[0].getChoose()) return 0;
    else return 1;
}

int Menu::levelMenu() {
    if (mapButtons[0].getChoose()) return 0;
    else if (mapButtons[1].getChoose()) return 1;
    else if (mapButtons[2].getChoose()) return 2;
    else if (mapButtons[3].getChoose()) return 3;
    else if (mapButtons[4].getChoose()) return 4;
    else return 5;
}

// int Menu::levelMenu() {
//     if (levelButtons[0].getChoose()) return 0;
//     else if (levelButtons[1].getChoose()) return 1;
//     else return 2;
// }

void Menu::getScore(int &score1, int &score2, int &score3, const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File score not opened" << std::endl;
        return;
    }
    std::vector <int> a;
    int x;
    while (file >> x) {
        a.push_back(x);
    }
    file.close();
    sort(a.begin(), a.end(), std::greater<int>());
    if (a.size() >= 3) {
        score1 = a[0];
        score2 = a[1];
        score3 = a[2];
    }
    else if (a.size() == 2) {
        score1 = a[0];
        score2 = a[1];
        score3 = 0;
    }
    else if (a.size() == 1) {
        score1 = a[0];
        score2 = 0;
        score3 = 0;
    }
    else {
        score1 = 0;
        score2 = 0;
        score3 = 0;
    }
}