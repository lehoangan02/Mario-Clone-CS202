#pragma
#include "raylib.h"
#include "../characters/Character.h"
class Obstacle {
protected:
	Vector2 position;
	Vector2 size;
	Texture2D texture;
public:
	Obstacle(Vector2 pos, Vector2 size, Texture2D tex);
	virtual ~Obstacle();
	virtual void Update(float deltaTime); // for dynamic obstacle
	virtual void Draw() = 0;
	virtual bool checkCollision(Character* character) = 0;
};
class StaticObstacle : public Obstacle {
public:
	StaticObstacle(Vector2 pos, Vector2 size, Texture2D tex);
	void Draw() override;
	bool checkCollision(Character* character) override;

};
class DynamicObstacle : public Obstacle {
protected:
	Vector2 velocity;
public:
	DynamicObstacle(Vector2 pos, Vector2 size, Texture2D tex, Vector2 velocity);
	void Update(float deltaTime) override;
	void Draw() override;
	bool checkCollision(Character* character) override;
};

