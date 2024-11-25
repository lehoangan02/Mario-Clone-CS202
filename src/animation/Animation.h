#pragma once
#include "raylib.h"
#include "raymath.h"
class Animation
{
public:
	Animation(Texture2D* texture, Vector2 imageCount, float switchTime);
	~Animation();
	void Update(int state, float deltaTime, bool faceRight);
	void Update(int state, float deltaTime);
public:
	Rectangle uvRect;

private:
	Vector2 imageCount;
	Vector2 currentImage;

	float totalTime;
	float switchTime;
};