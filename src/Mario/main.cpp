//#include "../Application.hpp"

//int main() {
//
//	
//    SetTargetFPS(60);
//    InitAudioDevice();
//
//    SetConfigFlags(FLAG_MSAA_4X_HINT);
//    InitWindow(1024, 768, "Game Window");
//    SetWindowState(FLAG_WINDOW_RESIZABLE);
//    ResourceManager::GetInstance()->LoadResources();
//    Application app;
//    app.run();
//    CloseAudioDevice();
//}

// #include "../characters/Enemy.hpp"
// #include "raylib.h"


  #include "../Application.hpp"


  #include "../levels/Level.hpp"
  int main() {
      const int screenWidth = 1024;
      const int screenHeight = 896;

      InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

      SetTargetFPS(60);
      LevelFactory& factory = LevelFactory::GetLevelFactory();
      Level* level = factory.CreateLevel(LevelFactory::LEVEL_101);

      while (!WindowShouldClose()) {

          BeginDrawing();
          ClearBackground(RAYWHITE);

          if(IsKeyPressed(KEY_P)) {
              level = factory.CreateLevel(LevelFactory::LEVEL_103);
          }
          level->update(GetFrameTime());

          level->render();
          EndDrawing();
      }

      CloseWindow();
  }

