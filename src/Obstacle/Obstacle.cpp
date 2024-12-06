#include <iostream>
#include "Obstacle.h"

Obstacle::Obstacle(Vector2 pos, Vector2 size, Texture2D tex) 
	: position(pos), size(size), texture(tex) {}
Obstacle::~Obstacle() {
	UnloadTexture(texture);
}
void Obstacle::Update(float deltaTime) {
	return;
}
StaticObstacle::StaticObstacle(Vector2 pos, Vector2 size, Texture2D tex)
	: Obstacle(pos, size, tex) {}
void StaticObstacle::Draw() {
	Rectangle sourceRect = { 0, 0, (float)texture.width, (float)texture.height };
	Rectangle destRect = { position.x, position.y, size.x, size.y };           
	Vector2 origin = { 0, 0 }; 

	DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
}
bool StaticObstacle::checkCollision(Character* character) {
	Rectangle obstacleRect = { position.x, position.y, size.x, size.y };
	Rectangle characterRect = { character->GetPosition().x, character->GetPosition().y, character->GetSize().x, character->GetSize().y };
	return CheckCollisionRecs(obstacleRect, characterRect);
}
DynamicObstacle::DynamicObstacle(Vector2 pos, Vector2 size, Texture2D tex, Vector2 velocity)
	: Obstacle(pos, size, tex), velocity(velocity) {}
void DynamicObstacle::Update(float deltaTime) {
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
}
void DynamicObstacle::Draw() {
	Rectangle sourceRect = { 0, 0, (float)texture.width, (float)texture.height };
	Rectangle destRect = { position.x, position.y, size.x, size.y };
	Vector2 origin = { 0, 0 };
	DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
}
bool DynamicObstacle::checkCollision(Character* character) {
	Rectangle obstacleRect = { position.x, position.y, size.x, size.y };
	Rectangle characterRect = { character->GetPosition().x, character->GetPosition().y,
									character->GetSize().x, character->GetSize().y};
	return CheckCollisionRecs(obstacleRect, characterRect);
}