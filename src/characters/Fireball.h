#include "raylib.h"
#include "raymath.h"

class Fireball {
public:
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    float scale;
    float maxDistance;
    Vector2 startPosition;
	Fireball(Vector2 pos, Vector2 vel, float scale = 1.0f, float maxDist = 1000.0f);
    ~Fireball();
    void Update(float deltaTime);
    void Draw();
    bool HasExceededMaxDistance();
};