#include "../characters/Character.h"
#include "../characters/Mario.h"
#include "../characters/Luigi.h"
#include <iostream>

//character
character::character() {
	position = { 350.0f , 620.0f };
	speed = 2;
	framesSpeed = 8;
	frameJump = 0;
	onair = false;
	jump = false;
};

//Mario
Mario::Mario() : character() {
	currentFrame = 0;
	texture = LoadTexture("../assets/textures/mario.png");
	frameRec = { 0.0f, 0.0f, (float)texture.width / 10, (float)texture.height };
};
void Mario::render() {
	float scale = 4.0f;
	Rectangle destRec = { position.x, position.y, frameRec.width * scale, frameRec.height * scale };
	DrawTexturePro(texture, frameRec, destRec, { 0, 0 }, 0.0f, WHITE);
}
void Mario::controller(int& framesCounter) {
	if (IsKeyDown(KEY_RIGHT)) {
		position.x += 4;
		framesCounter++;
		if (!onair) {
			if (framesCounter >= (60 / framesSpeed))
			{
				framesCounter = 0;
				currentFrame++;

				if (currentFrame > 3) currentFrame = 1;

			}
		}
	}
	if (IsKeyDown(KEY_LEFT)) {
		position.x -= 4;
		framesCounter++;
		if (!onair) {
			if (framesCounter >= (60 / framesSpeed))
			{
				framesCounter = 0;
				currentFrame++;

				if (currentFrame > 7) currentFrame = 5;
			}
		}
	}
	if (IsKeyReleased(KEY_RIGHT) || (currentFrame == 8 && !onair)) {
		currentFrame = 0;
	}
	if (IsKeyReleased(KEY_LEFT) || (currentFrame == 9 && !onair)) {
		currentFrame = 4;
	}
	if (IsKeyPressed(KEY_UP) && !onair) {
		jump = true;
		onair = true;
	}
	if (jump && frameJump < 40) {
		frameJump++;
		position.y -= 5;
		if (currentFrame == 1 || currentFrame == 2 || currentFrame == 3 || currentFrame == 0 || currentFrame == 8) currentFrame = 8;
		else {
			currentFrame = 9;
		}
		if (frameJump == 40) jump = false;
	}
	else if (!jump && frameJump > 0) {
		frameJump--;
		position.y += 5;
		if (currentFrame == 1 || currentFrame == 2 || currentFrame == 3 || currentFrame == 0 || currentFrame == 8) currentFrame = 8;
		else currentFrame = 9;
		if (frameJump == 0) onair = false;
	}
	frameRec.x = (float)currentFrame * (float)texture.width / 10;
}

//Luigi
Luigi::Luigi() : character() {
	currentFrame = 6;
	texture = LoadTexture("../assets/textures/luigi.png");
	frameRec = { 0.0f, 0.0f, (float)texture.width / 13, (float)texture.height };
};
void Luigi::render() {
	float scale = 3.5f;
	Rectangle destRec = { position.x, position.y, frameRec.width * scale, frameRec.height * scale };
	DrawTexturePro(texture, frameRec, destRec, { 0, 0 }, 0.0f, WHITE);
};
void Luigi::controller(int& framesCounter) {
	if (IsKeyDown(KEY_RIGHT)) {
		position.x += 4;
		framesCounter++;
		if (!onair) {
			if (framesCounter >= (60 / framesSpeed))
			{
				framesCounter = 0;
				currentFrame--;
				if (currentFrame < 7) currentFrame = 9;
			}
		}
	}
	if (IsKeyDown(KEY_LEFT)) {
		position.x -= 4;
		framesCounter++;
		if (!onair) {
			if (framesCounter >= (60 / framesSpeed))
			{
				framesCounter = 0;
				currentFrame++;

				if (currentFrame > 4) currentFrame = 2;
			}
		}
	}
	if (IsKeyReleased(KEY_RIGHT) || (currentFrame == 11 && !onair)) {
		currentFrame = 6;
	}
	if (IsKeyReleased(KEY_LEFT) || (currentFrame == 0 && !onair)) {
		currentFrame = 5;
	}
	if (IsKeyPressed(KEY_UP) && !onair) {
		jump = true;
		onair = true;
	}
	if (jump && frameJump < 40) {
		frameJump++;
		position.y -= 5;
		for (int i = 5; i >= 2; i--) {
			if (currentFrame == i) {
				currentFrame = 0;
				break;
			}
		}
		for (int i = 6; i <= 9; i++) {
			if (currentFrame == i) {
				currentFrame = 11;
				break;
			}
		}
		if (frameJump == 40) jump = false;
	}
	else if (!jump && frameJump > 0) {
		frameJump--;
		position.y += 5;
		if (frameJump == 0) onair = false;
	}
	frameRec.x = (float)currentFrame * (float)texture.width / 13;
}

//Factory
character* characterFactory::currentCharacter = nullptr;
void characterFactory::deleteCharacter() {
	delete currentCharacter;
	currentCharacter = nullptr;
}
character* characterFactory::createCharacter(characterType type) {
	deleteCharacter();
	switch (type) {
	case MARIO:
		currentCharacter = new Mario();
		break;
	case LUIGI:
		currentCharacter = new Luigi();
		break;
	default:
		currentCharacter = nullptr;
	}
	return currentCharacter;

}




