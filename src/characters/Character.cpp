#include "Character.h"
#include <iostream>
#define scale 3 //scale of character
using namespace std;
Character::Character(float speed, float jumpHeight) 
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->faceRight = true;
	this->state = 0;
	this->velocity = { 0.0f, 0.0f };
	this->canJump = false;
	position = Vector2{ 20 , 0 };
}

Character::~Character()
{
}
Vector2 Character::GetCenter() {
	return Vector2{ position.x + size.x / 2, position.y + size.y / 2 };
}
void Character::accelerate(Vector2 acceleration, float deltaTime) {
	velocity.x += acceleration.x * deltaTime;
	if (velocity.x > 10.0f)
			velocity.x = 10.0f;
	else if (velocity.x < -10.0f)
		velocity.x = -10.0f;
	velocity.y += acceleration.y * deltaTime;
}
void Character::control(float& accX, bool enabled) {
	if (!enabled) {
		velocity.x = 0;
		return;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		accX = fabs(speed);
	}
	else if (IsKeyDown(KEY_LEFT)) {
		accX = -fabs(speed);
	}
	else {
		velocity.x = 0.0f;
	}
	if (IsKeyPressed(KEY_SPACE) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * 9.81f * jumpHeight);
	}
}

void Character::Draw()
{
	Rectangle sourceRec = animation.uvRect; // The part of the texture to use for drawing
	Rectangle destRec = { position.x, position.y, fabs(sourceRec.width) * scale, sourceRec.height * scale }; // Destination rectangle with scaling
	float rotation = 0.0f;
	Vector2 origin = { 0.0f, 0.0f };
	DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);
};

Mario::Mario() : Character(500.0f, 3.0f) {
	texture = LoadTexture("assets/textures/mario.png");
	Vector2 imageCount = { 10,1 };
	float switchTime = 0.1f;
	animation = Animation(&texture, imageCount, switchTime);
	size = { (float) texture.width /10 * scale, (float)texture.height * scale };
}
Luigi::Luigi() : Character(500.0f, 3.0f) {
	texture = LoadTexture("assets/textures/luigi.png");
	Vector2 imageCount = { 10,1 };
	float switchTime = 0.1f;
	animation = Animation(&texture, imageCount, switchTime);
	size = { (float)texture.width / 10 * scale, (float)texture.height * scale };
}
void Mario::Update(float deltaTime) {
	if (velocity.y > 0.02f) canJump = false; //handle double jump 
	if (velocity.x == 0.0f) {
		state = 0;
	}
	else {
		state = 1;
		if (velocity.x > 0.0f) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
	}
	animation.Update(state, deltaTime, faceRight);
	setPosition(Vector2{ position.x + velocity.x, position.y + velocity.y });
}
void Luigi::Update(float deltaTime) {
	if (velocity.y > 0.02f) canJump = false; //handle double jump 
	if (velocity.x == 0.0f) {
		state = 0;
	}
	else {
		state = 1;
		if (velocity.x > 0.0f) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
	}
	animation.Update(state, deltaTime, faceRight);
	setPosition(Vector2{ position.x + velocity.x, position.y + velocity.y });
}
Character* CharacterFactory::currentCharacter = nullptr;
void CharacterFactory::deleteCharacter() {
	delete currentCharacter;
	currentCharacter = nullptr;
}
Character* CharacterFactory::createCharacter(CharacterType type) {
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