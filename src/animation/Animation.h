#pragma once
#include "raylib.h"
#include "raymath.h"
class Animation
{
public:
	Animation() = default;
	Animation(Texture2D* texture, Vector2 imageCount, float switchTime);
	~Animation();
	void Update(int state, float deltaTime, bool faceRight, bool& fire);
	void Update(float deltaTime);
public:
	Rectangle uvRect;

	Vector2 currentImage;

private:
	Vector2 imageCount;

	float totalTime;
	float switchTime;
};