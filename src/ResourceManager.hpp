#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include "raylib.h"
#include <map>
#include <string>

class ResourceManager {
private:
    static ResourceManager* instance;
    Font commonFont;
    std::map<std::string, Texture2D> textures;

    ResourceManager(); // Constructor private
public:
    ~ResourceManager();
    static ResourceManager* GetInstance();

    Font GetFont() const;
    Texture2D GetTexture(const std::string& name);
    void LoadResources();
    void UnloadResources();
};

class ResourceInitializer {
public:
    static void InitializeResources() {
        // Nạp tài nguyên trước khi tạo cửa sổ
        ResourceManager::GetInstance()->LoadResources();
    }
};


#endif
