#include "Fireball.h"

const float FIREGRAVITY = 1000.0f; // Gravity constant
const float FIRESPEED = 1000.0f;
Fireball::Fireball() {
    position = { 0,0 };
    velocity = { 0,0 };
    texture = LoadTexture("assets/textures/Ball.png"); // Load the fireball texture
    float switchTime = 0.06f;
    animation = Animation(&texture, Vector2{ 4,1 }, switchTime);

    this->scale = 3.0f;
    this->active = false;
}

void Fireball::Update(float deltaTime) {
    if (this->active) {
        // Apply gravity
        velocity.y += FIREGRAVITY * deltaTime;

        // Update position
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

    }
    animation.Update(deltaTime);
}

void Fireball :: Bounce() {
	velocity.y = -velocity.y * 0.7f;
}
void Fireball::Draw() {
    if (active) {
        Rectangle sourceRect = animation.uvRect;
  /*      std::cout << "draw" << std::endl;*/
        Rectangle destRect = { position.x, position.y, float(fabs(texture.width / 4) * scale), float(texture.height * scale)};
		/*std::cout << animation.uvRect.width * scale << " " << animation.uvRect.height * scale << std::endl;*/
        /*std::cout << position.x << " " << position.y << std::endl;*/
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
    }
}

void Fireball::Shoot(Vector2 pos, Vector2 direction) {
    position = pos;
    this->velocity = { direction.x * FIRESPEED, direction.y * FIRESPEED };
    active = true;
}

bool Fireball::IsActive() const {
    return active;
}

void Fireball::Deactivate() {
    active = false;
}

FirePool::FirePool(int size) {
    fireballs.resize(size);
}

Fireball* FirePool::GetAvailableFireBall(Vector2 position, Vector2 direction) {
    for (int i = 0; i < fireballs.size(); i++) {
        if (!fireballs[i].IsActive()) {
            fireballs[i].Shoot(position, direction);
            return &fireballs[i];
        }
    }
    return nullptr;
}

void FirePool::Update() {
    for (int i = 0; i < fireballs.size(); i++) {
        fireballs[i].Update(GetFrameTime());
    }
}

void FirePool::Draw() {
    for (int i = 0; i < fireballs.size(); i++) {
        fireballs[i].Draw();
    }
}