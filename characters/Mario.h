#pragma once
#include "../characters/Character.h"

class Mario : public character {
private:
	Texture2D texture;
	Rectangle frameRec;
	int currentFrame;
	float velocityY;
public:
	Mario();
	void render() override;
	void controller(int& framesCounter) override;
};