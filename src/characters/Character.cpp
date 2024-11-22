#include "Character.h"
#include <iostream>
using namespace std;
Character::Character(Texture2D* texture, Vector2 imageCount, float switchTime, float speed, float jumpHeight) : animation(texture, imageCount, switchTime)
{
	this->texture = *texture;
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->faceRight = true;
	this->state = 0;;
	position = { 350.0f, 280.0f };
	int scale = 3;
	size = { (float) (*texture).width/10 * scale, (float) texture->height *scale };

}

Character::~Character()
{
}
Vector2 Character::GetCenter() {
	return Vector2{ position.x + size.x / 2, position.y + size.y / 2 };
}
void Character::Update(float deltaTime)
{
	 //change for slowing down
	velocity = { 0.0f, 0.0f };
	if (IsKeyDown(KEY_RIGHT)) {
		velocity.x += speed;
	}
	if (IsKeyDown(KEY_LEFT)) {
		velocity.x -= speed;
	}
	if (IsKeyPressed(KEY_SPACE) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * 0.981f * jumpHeight);
	}
	velocity.y += 0.981f * deltaTime;
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
	position.x += (velocity.x);
	position.y += (velocity.y);
}

void Character::Draw()
{
	int scale = 3;
	Rectangle sourceRec = animation.uvRect; // The part of the texture to use for drawing
	Rectangle destRec = { position.x, position.y, fabs(sourceRec.width) * scale, sourceRec.height * scale }; // Destination rectangle with scaling
	float rotation = 0.0f;
	Vector2 origin = { 0.0f, 0.0f };
	DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);
};


//Character* CharacterFactory::currentCharacter = nullptr;
//void CharacterFactory::deleteCharacter() {
//	delete currentCharacter;
//	currentCharacter = nullptr;
//}
//Character* CharacterFactory::createCharacter(CharacterType type) {
//	deleteCharacter();
//	switch (type) {
//	case MARIO:
//		currentCharacter = new Mario();
//		break;
//	case LUIGI:
//		currentCharacter = new Luigi();
//		break;
//	default:
//		currentCharacter = nullptr;
//	}
//	return currentCharacter;
//
//}