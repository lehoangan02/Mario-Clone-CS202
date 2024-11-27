

#include "Application.hpp"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 768, "Game Window");
    ResourceManager::GetInstance()->LoadResources();
    
    Application app;
    app.run();
}
