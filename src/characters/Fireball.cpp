#include "Fireball.h"


Fireball::Fireball(Vector2 pos, Vector2 vel, float scale, float maxDist) {
    position = pos;
    velocity = vel;
    texture = LoadTexture("assets/textures/Ball.png"); // Load the fireball texture
    float switchTime = 0.1f;
    animation = Animation(&texture, Vector2 { 4,1 }, switchTime);
    this->scale = scale;
    this->maxDistance = maxDist;
    this->startPosition = pos;
}

Fireball::~Fireball() {
    /*UnloadTexture(texture);*/ // Unload the texture when the fireball is destroyed
}

void Fireball::Update(float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
	animation.Update(deltaTime);
}

void Fireball::Draw() {
    Rectangle sourceRect = animation.uvRect;

    // Define the destination rectangle (where to draw the texture on the screen)
    Rectangle destRect = { position.x, position.y, static_cast<float>(fabs(texture.width / 4) * scale), texture.height * scale };
    // Define the origin point (center of the texture)
    Vector2 origin = { (texture.width * scale) / 2, (texture.height * scale) / 2 };

    // Draw the texture with the specified rectangles
    DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
}

bool Fireball::HasExceededMaxDistance() {
    float distanceTraveled = sqrtf(powf(position.x - startPosition.x, 2) + powf(position.y - startPosition.y, 2));
    return distanceTraveled > maxDistance;
}