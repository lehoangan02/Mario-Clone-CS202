#include "../Application.hpp"

int main() {

	
    SetTargetFPS(60);
    InitAudioDevice();

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 768, "Game Window");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    ResourceManager::GetInstance()->LoadResources();
    Application app;
    app.run();
    CloseAudioDevice();
}

 #include "../characters/Enemy.hpp"
 #include "raylib.h"


  /*#include "../Application.hpp"
  int main() {
      const int screenWidth = 1024;
      const int screenHeight = 896;

      InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

      SetTargetFPS(60);
    
      Texture2D starmanTexture = LoadTexture("assets/textures/StarMan.png");
      StarMan* starman = new StarMan(
          Vector2{ 200, 200 },
          Vector2{ 0, 0 },
          Vector2{ 60, 60 },
          starmanTexture,
          Vector2{ 50, 50 }
      );
      
      while (!WindowShouldClose()) {

          BeginDrawing();
          ClearBackground(RAYWHITE);
          if (IsKeyPressed(KEY_A)) {
              starman->onNotify();
          }
          
          starman->Update(GetFrameTime());
          starman->Draw();
          EndDrawing();
      }

      CloseWindow();
  }*/

