#include "Item.h"
#include <iostream>
Item::Item(Vector2 pos, Vector2 size, Texture2D tex, int totalFrames, float switchTime, Vector2 velocity)
	: position(pos), size(size), texture(tex), totalFrames(totalFrames), switchTime(switchTime), velocity(velocity) {
	currentFrame = 0;
	elapsedTime = 0.0f;
	frameSize = { (float)(tex.width / totalFrames), (float)tex.height };
	uvRect = { 0.0f, 0.0f, frameSize.x, frameSize.y };
}
Item::~Item() {
	UnloadTexture(texture);
}
void Item::Update(float deltaTime) {
	elapsedTime += deltaTime;
	if (elapsedTime >= switchTime) {
		elapsedTime = 0.0f;
		currentFrame = (currentFrame + 1) % totalFrames;
		uvRect.x = currentFrame * frameSize.x;
	}
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	if (position.x < 0 || position.x + size.x > GetScreenWidth()) {
		velocity.x *= -1;
	}
	if (position.y < 0 || position.y + size.y > GetScreenHeight()) {
		velocity.y *= -1;
	}
}
void Item::Draw() {
	Rectangle destRect = { position.x, position.y, size.x, size.y };
	Vector2 origin = { 0, 0 }; 

	DrawTexturePro(texture, uvRect, destRect, origin, 0.0f, WHITE);
}
Coin::Coin(Vector2 pos, Vector2 size, Texture2D tex, Vector2 velocity) 
	: Item(pos, size, tex, COIN_FRAME_COUNT, COIN_FRAME_TIME, velocity) {}
void Coin::applyEffect(Character* character) {
	return;
}
Mushroom::Mushroom(Vector2 pos, Vector2 size, Texture2D tex, Vector2 velocity) 
	: Item(pos, size, tex, MUSHROOM_FRAME_COUNT, MUSHROOM_FRAME_TIME, velocity) {}
void Mushroom::applyEffect(Character* character) {
	return;
}
FireFlower::FireFlower(Vector2 pos, Vector2 size, Texture2D tex, Vector2 velocity) 
	: Item(pos, size, tex, FIREFLOWER_FRAME_COUNT, FIREFLOWER_FRAME_TIME, velocity) {}
void FireFlower::applyEffect(Character* character) {
	return;
}

