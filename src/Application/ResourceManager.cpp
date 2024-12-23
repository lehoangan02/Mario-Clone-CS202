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
    textures["playTexture"] = LoadTexture("./assets/textures/playMenu.png");
    textures["settingTexture"] = LoadTexture("./assets/textures/settingMenu.png");
    textures["settingCharacter"] = LoadTexture("./assets/textures/characterMenu.png");
    textures["settingMap"] = LoadTexture("./assets/textures/mapMenu.png");
    textures["settingLevel"] = LoadTexture("./assets/textures/levelMenu.png");
    textures["highScoreTexture"] = LoadTexture("./assets/textures/highScoreMenu.png");
    textures["inforTexture"] = LoadTexture("./assets/textures/inforMenu.png");

    textures["quitTexture"] = LoadTexture("./assets/textures/quit.png");


    textures["goomba1"] = LoadTexture("assets/textures/Goomba_Walk1.png");
    textures["goomba2"] = LoadTexture("assets/textures/Goomba_Walk2.png");
    textures["goomba3"] = LoadTexture("assets/textures/Goomba_Flat.png");

    textures["piranha1"] = LoadTexture("assets/textures/PiranhaPlant_0.png");
    textures["piranha2"] = LoadTexture("assets/textures/PiranhaPlant_1.png");

    textures["shyguy1"] = (LoadTexture("assets/textures/ShyGuy1.png"));
    textures["shyguy2"] = (LoadTexture("assets/textures/ShyGuy2.png"));
    textures["shyguy3"] = (LoadTexture("assets/textures/ShyGuy3.png"));
    textures["shyguy4"] = (LoadTexture("assets/textures/ShyGuy4.png"));
    textures["shyguy5"] = (LoadTexture("assets/textures/ShyGuy5.png"));
    textures["shyguy6"] = (LoadTexture("assets/textures/ShyGuy6.png"));

    textures["koopa1"] = (LoadTexture("assets/textures/kt1.png"));
    textures["koopa2"] = (LoadTexture("assets/textures/kt2.png"));
    textures["koopa3"] = (LoadTexture("assets/textures/kt3.png"));
    textures["koopa4"] = (LoadTexture("assets/textures/kt4.png"));
    textures["koopa5"] = (LoadTexture("assets/textures/kt5.png"));
    textures["koopa6"] = (LoadTexture("assets/textures/kt6.png"));

    textures["bullet1"] = (LoadTexture("assets/textures/bullet1.png"));
    textures["bullet2"] = (LoadTexture("assets/textures/bullet2.png"));
    textures["bullet3"] = (LoadTexture("assets/textures/bullet3.png"));
    textures["bullet4"] = (LoadTexture("assets/textures/bullet4.png"));

    textures["lakitu1"] = (LoadTexture("assets/textures/Lakitu1.png"));
    textures["lakitu2"] = (LoadTexture("assets/textures/Lakitu2.png"));
    textures["lakitu3"] = (LoadTexture("assets/textures/Lakitu3.png"));
    textures["lakitu4"] = (LoadTexture("assets/textures/Lakitu4.png"));
    textures["lakitu5"] = (LoadTexture("assets/textures/Lakitu5.png"));
    textures["lakitu6"] = (LoadTexture("assets/textures/Lakitu6.png"));
    textures["lakitu7"] = (LoadTexture("assets/textures/Lakitu7.png"));
    textures["lakitu8"] = (LoadTexture("assets/textures/Lakitu8.png"));
    textures["lakitu9"] = (LoadTexture("assets/textures/Lakitu9.png"));
    textures["lakitu10"] = (LoadTexture("assets/textures/Lakitu10.png"));
    textures["lakitu11"] = (LoadTexture("assets/textures/Lakitu11.png"));


    textures["pause"] = (LoadTexture("assets/textures/pause.png"));
    textures["continue"] = (LoadTexture("assets/textures/continue.png"));
    textures["replay"] = (LoadTexture("assets/textures/replay.png"));
    textures["home"] = (LoadTexture("assets/textures/home.png"));
    
    textures["pauseGame"] = (LoadTexture("assets/textures/pauseGame.png"));
    textures["winGame"] = (LoadTexture("assets/textures/winGame.png"));
    textures["loseGame"] = (LoadTexture("assets/textures/loseGame.png"));
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
