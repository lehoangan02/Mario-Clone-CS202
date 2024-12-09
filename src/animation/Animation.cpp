#include "Animation.h"
#include <iostream>
using namespace std;
Animation::Animation(Texture2D* texture, Vector2 imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0;
	currentImage.x = 0;
	if (texture == nullptr) {
		std::cerr << "Texture is null" << std::endl;
	}
	uvRect.width = texture->width / imageCount.x;
	// std::cout << "Width: " << uvRect.width << std::endl;
	uvRect.height = texture->height;
	// std::cout << "Height: " << uvRect.height << std::endl;
	uvRect.y = 0;
}

Animation::~Animation()
{
}
void Animation::Update(int state, float deltaTime, bool faceRight, bool& fire, bool& brake) {
	currentImage.y = 0; // modify this if texture having states
	if (state == 0) currentImage.x = 0;
	else if (state == 2) currentImage.x = 5;
	else if (state == 3)
	{
		totalTime += 0.02f;
		currentImage.x = 6;
		//std::cout << totalTime << std::endl;
		if (totalTime >= switchTime) {
			totalTime = 0;
			fire = false;
		}
	}
	else if (state == 4) {
		totalTime += 0.015f;
		currentImage.x = 4;
		if (totalTime >= switchTime) {
			totalTime = 0;
			brake= false;
		}
	}
	else if (state == 1) {
		totalTime += deltaTime;
		if (totalTime >= switchTime) {
			totalTime = 0;
			currentImage.x++;
			if (currentImage.x >= 4) currentImage.x = 1;
		}
	}
	if (faceRight) {
		uvRect.x = currentImage.x * uvRect.width;
		uvRect.width = fabs(uvRect.width);
	}
	else
	{
		uvRect.x = (currentImage.x) * fabs(uvRect.width);
		uvRect.width = -fabs(uvRect.width);
	};
}
void Animation::Update(float deltaTime) {
	currentImage.y = 0; // modify this if texture having states
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime = 0;
		currentImage.x++;
		if (currentImage.x >= 4) currentImage.x = 0;
	}
	uvRect.x = currentImage.x * uvRect.width;
	uvRect.width = fabs(uvRect.width);
}