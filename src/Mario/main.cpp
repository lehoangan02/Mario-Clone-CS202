#include "../Application.hpp"
#include "../Sound/Audio.h"
int main() {
	SetTargetFPS(60);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 768, "Game Window");
	InitAudioDevice();
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    ResourceManager::GetInstance()->LoadResources();

    Application app;
    app.run();
	CloseAudioDevice();
}