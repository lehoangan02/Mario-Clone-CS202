#include "raylib.h"
#include "raymath.h"
#include "../animation//Animation.h"

#include <vector>
#include <iostream>
class Fireball {
public:
    Vector2 position;
    Vector2 velocity;
    bool active;
public:
    Texture2D texture;
    float scale;
	Animation animation;
	Fireball();
	void Shoot(Vector2 pos, Vector2 direction);
    bool IsActive() const;
    void Deactivate();
    void Update(float deltaTime);
    void Draw();
    void Bounce();
    Vector2 getPosition() { return position; };
    Vector2 getSize() { return { animation.uvRect.width*scale, animation.uvRect.height*scale }; };
};
class FirePool {
public:
	std::vector<Fireball> fireballs;

public:
    FirePool(int size);
    Fireball* GetAvailableFireBall(Vector2 position, Vector2 direction);
    void Update();
    void Draw();
};