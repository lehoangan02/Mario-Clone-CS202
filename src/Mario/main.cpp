#include "../Application.hpp"

int main() {
	SetTargetFPS(60);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 768, "Game Window");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    ResourceManager::GetInstance()->LoadResources();

    Application app;
    app.run();

    //const int screenWidth = 1024;
    //const int screenHeight = 768;

    //InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    //Texture2D coinTexture = LoadTexture("assets/textures/Coin.png");
    //Texture2D mushroomTexture = LoadTexture("assets/textures/MagicMushroom.png");
    //Texture2D fireflowerTexture = LoadTexture("assets/textures/FireFlower.png");
    //Texture2D starmanTexture = LoadTexture("assets/textures/starman.png");
    //FireFlower* fireflower = new FireFlower(
    //    Vector2{ 200, 300 },
    //    Vector2{ 0, 0 },
    //    Vector2{ 50, 50 },
    //    fireflowerTexture
    //);
    //IdleCoin* coin1 = new IdleCoin(
    //    Vector2{ 300, 300 },
    //    Vector2{ 20, 50 },
    //    coinTexture
    //);
    //StarMan* starman = new StarMan(
    //    Vector2{ 200, 200 },
    //    Vector2{ 0, 0 },
    //    Vector2{ 60, 60 },
    //    starmanTexture,
    //    Vector2{ 2.0f, 2.0f }
    //);
    //Coin* coin = new Coin(
    //    Vector2{ 100, 500 },   //Start position
    //    Vector2{ 100, 300 },    //End position
    //    Vector2{ 40,100 },      // size of coin
    //    coinTexture,
    //    Vector2{ 0, 400 }     //velocity
    //);
    //Mushroom* mushroom = new Mushroom(
    //    Vector2{ 200, 100 },   // Start position
    //    Vector2{ 0, 0 },   // End position
    //    Vector2{ 60, 60 },    // Size
    //    mushroomTexture,     // Texture
    //    Vector2{ 100, 0 }      // Velocity
    //);
    //// AABBox MushroomBox = AABBox(mushroom -> GetPosition(), mushroom -> GetSize());
    //LevelFactory& factory = LevelFactory::GetLevelFactory();
    //Level* level = factory.CreateLevel(LevelFactory::LEVEL_101);
    //Texture t = LoadTexture("assets/textures/mario.png");
  
    //float deltatime;
    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //while (!WindowShouldClose())
    //{
    //    deltatime = GetFrameTime();

    //    if (IsKeyPressed(KEY_A))
    //    {
    //        coin->onNotify();
    //    }
    //    if (IsKeyPressed(KEY_B))
    //    {
    //        mushroom->onNotify();

    //    }
    //    if (IsKeyPressed(KEY_C))
    //    {
    //        fireflower->onNotify();
    //    }
    //    if (IsKeyPressed(KEY_D))
    //    {
    //        starman->onNotify();
    //    }
    //    if (IsKeyPressed(KEY_E)) {
    //        starman->setHit();
    //    }
    //    coin1->Update(deltatime);
    //    coin->Update(deltatime);
    //    mushroom->Update(deltatime);
    //    starman->Update(deltatime);
    //    fireflower->Update(deltatime);
    //    starman->Update(deltatime);

    //   


    //    BeginDrawing();
    //    ClearBackground(Color{ 105, 147, 245, 255 });
    //    coin->Draw();
    //    coin1->Draw();
    //    mushroom->Draw();
    //    starman->Draw();
    //    fireflower->Draw();
    //    starman->Draw();
    //    
    //    DrawBoundingBox(mushroom->GetPosition(), mushroom->GetSize(), RED);
    //    DrawBoundingBox(fireflower->GetPosition(), fireflower->GetSize(), RED);
    //    DrawBoundingBox(starman->GetPosition(), starman->GetSize(), RED);
    //    // DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);
    //    // DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
    //    EndDrawing();

    //}

    //CloseWindow();

    //return 0;
}