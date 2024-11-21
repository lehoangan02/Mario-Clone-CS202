#include "../Animation.h"
#include <iostream>
using namespace std;
Animation::Animation(Texture2D* texture, Vector2 imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0;
	currentImage.x = 0;

	uvRect.width = texture->width / 10;
	uvRect.height = texture->height;
	uvRect.y = 0;
}

Animation::~Animation()
{
}
void Animation::Update(int state, float deltaTime, bool faceRight) {
	currentImage.y = 0; // modify this if texture having states
	totalTime += deltaTime;
	if (state == 0) currentImage.x = 0;
	else {
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
	} 
}
;