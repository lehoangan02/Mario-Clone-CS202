#include "Application.hpp"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 768, "Game Window");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    ResourceManager::GetInstance()->LoadResources();

    Application app;
    app.run();
}