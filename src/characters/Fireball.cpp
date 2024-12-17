#include "Fireball.h"


Fireball::Fireball(Vector2 pos, Vector2 vel, float scale, float maxDist) {
    position = pos;
    velocity = vel;
    texture = LoadTexture("assets/textures/fireball.png"); // Load the fireball texture
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
}

void Fireball::Draw() {
    // Draw the fireball texture with scaling
    DrawTextureEx(texture, { position.x - (texture.width * scale) / 2, position.y - (texture.height * scale) / 2 }, 0.0f, scale, WHITE);
}

bool Fireball::HasExceededMaxDistance() {
    float distanceTraveled = sqrtf(powf(position.x - startPosition.x, 2) + powf(position.y - startPosition.y, 2));
    return distanceTraveled > maxDistance;
}