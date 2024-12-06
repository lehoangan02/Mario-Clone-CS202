#pragma once
#include "raylib.h"
#include "raymath.h"
class Animation
{
public:
	Animation() = default;
	Animation(Texture2D* texture, Vector2 imageCount, float switchTime);
	~Animation();
	void Update(int state, float deltaTime, bool faceRight, bool& fire, bool& brake);
	void Update(float deltaTime);
public:
	Rectangle uvRect;

private:
	Vector2 imageCount;
	Vector2 currentImage;
	Vector2 prevImage;

	float totalTime;
	float switchTime;
};