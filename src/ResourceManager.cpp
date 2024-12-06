#include "ResourceManager.hpp"

ResourceManager* ResourceManager::instance = nullptr;
ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {
    UnloadResources();
}

ResourceManager* ResourceManager::GetInstance() {
    if (instance == nullptr) {
        instance = new ResourceManager();
    }
    return instance;
}

void ResourceManager::LoadResources() {
    commonFont = LoadFontEx("./assets/Font/InterBold.ttf", 50, NULL, 255);
    textures["pageTexture"] = LoadTexture("./assets/textures/GUI.png");
    textures["playTexture"] = LoadTexture("./assets/textures/play.png");
    textures["settingTexture"] = LoadTexture("./assets/textures/setting.png");
    textures["highScoreTexture"] = LoadTexture("./assets/textures/highScore.png");
    textures["inforTexture"] = LoadTexture("./assets/textures/infor.png");

    textures["mario"] = LoadTexture("./assets/textures/mario.png");
}

void ResourceManager::UnloadResources() {
    UnloadFont(commonFont);
    for (auto& pair : textures) {
        UnloadTexture(pair.second);
    }
}

Font ResourceManager::GetFont() const {
    return commonFont;
}

Texture2D ResourceManager::GetTexture(const std::string& name) {
    return textures.at(name);
}
