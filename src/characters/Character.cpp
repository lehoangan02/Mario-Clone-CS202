#include "Character.h"
#include <iostream>
using namespace std;
Character::Character(float speed, float jumpHeight) 
{
	this->form = 0;
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->faceRight = true;
	this->state = 0;
	this->velocity = { 0.0f, 0.0f };
	this->canJump = false;
	this->scale = 3.0f;
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
	if (IsKeyPressed(KEY_K)) {
		form = 2;
		size = { (float)textures[form].width / imageCounts[form].x * scale, (float)textures[form].height * scale };
		animation.uvRect = { 0.0f, 0.0f, (float)textures[form].width / imageCounts[form].x, (float)textures[form].height };
	}
	if (IsKeyPressed(KEY_J)) {
		form = 1;
		size = { (float)textures[form].width / imageCounts[form].x * scale, (float)textures[form].height * scale };
		animation.uvRect = { 0.0f, 0.0f, (float)textures[form].width / imageCounts[form].x, (float)textures[form].height };
	}
	if (form == 2 && IsKeyPressed(KEY_M)) {
	}
}

void Character::Draw()
{
	Rectangle sourceRec = animation.uvRect; // The part of the texture to use for drawing
	Rectangle destRec = { position.x, position.y, fabs(sourceRec.width) * scale, sourceRec.height * scale }; // Destination rectangle with scaling
	float rotation = 0.0f;
	Vector2 origin = { 0.0f, 0.0f };
	DrawTexturePro(textures[form], sourceRec, destRec, origin, rotation, WHITE);
};

Mario::Mario() : Character(500.0f, 3.0f) {
	textures.push_back(LoadTexture("assets/textures/marioSmall.png"));
	textures.push_back(LoadTexture("assets/textures/marioBig.png"));
	textures.push_back(LoadTexture("assets/textures/marioFire.png"));
	imageCounts.push_back({ 6,1 });
	imageCounts.push_back({ 6,1 });
	imageCounts.push_back({ 7,1 });
	float switchTime = 0.1f;
	animation = Animation(&textures[form], imageCounts[form], switchTime);
	size = { (float) textures[form].width / (imageCounts[form].x) * scale, (float)textures[form].height * scale};
}
Luigi::Luigi() : Character(500.0f, 3.0f) {
	textures.push_back(LoadTexture("assets/textures/marioSmall.png"));
	textures.push_back(LoadTexture("assets/textures/marioBig.png"));
	Vector2 imageCount = { 6,1 };
	float switchTime = 0.1f;
	animation = Animation(&textures[form], imageCount, switchTime);
	size = { (float)textures[form].width / (imageCount.x) * scale, (float)textures[form].height * scale };
}
void Mario::Update(float deltaTime) {
	if (velocity.y > 0.2f) canJump = false; //handle double jump 
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