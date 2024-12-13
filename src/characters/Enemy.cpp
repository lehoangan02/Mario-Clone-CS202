#include "Enemy.hpp"

#include "raylib.h"

void Enemy::accelerate(float deltaTime) {
    const float gravity = 9.8f; 
    speed.y += gravity * deltaTime; 
    position.x += speed.x * deltaTime; 
    position.y += speed.y * deltaTime; 
}


void Enemy::flipDirection() {
    speed.x *= -1;
}

void Enemy::hit() {
    isDead = true;
}

slidingDirection Enemy::getDirection() const {
    if (isRight) return slidingDirection::right;
    else if (isDown) return slidingDirection::down;
    else return slidingDirection::left;
}

void Enemy::setDirection(slidingDirection direction) {
    switch (direction) {
    case slidingDirection::right:
        isRight = true;
        isDown = false;
        break;
    case slidingDirection::down:
        isRight = false;
        isDown = true;
        break;
    case slidingDirection::left:
        isRight = false;
        isDown = false;
        break;
    default:
        break;
    }
}

void Enemy::render() {
    DrawTexture(texture, position.x, position.y, WHITE);
}

Goomba::Goomba(Vector2 position) : Enemy(position) {
    this->position = position;
    this->originPosition = position;
    texture = LoadTexture("assets/textures/Goomba_Walk1.png");
    textures.push_back(LoadTexture("assets/textures/Goomba_Walk1.png"));
    textures.push_back(LoadTexture("assets/textures/Goomba_Walk2.png"));
    textures.push_back(LoadTexture("assets/textures/Goomba_Flat.png"));
    size = { 32, 32 };
    speed = { 4, 0 };
    isRight = false;
    isDown = false;
    isDead = false;
    isDying = false;
}

void Goomba::hit() {
    if (isCollisionTrue) {
        this->texture = textures[2];           
    }
    isDying = true;              
        dyingTime = 0.0f; 
}
  

void Goomba::update(float deltaTime) {
    if (isDying) {
        dyingTime += deltaTime;
        if (dyingTime >= 1.0f) {
            isDead = true;
            isDying = false;
        }
        return;
    }
    if (isDead) return;



    if (isRight) {
        position.x += speed.x *deltaTime; 
    } else {
        position.x -= speed.x *deltaTime; 
    }

    timer += deltaTime;
    if (timer >= animationTime) {
        timer -= animationTime; 
        currentTextureIndex = (currentTextureIndex + 1) % 2; 
        texture = textures[currentTextureIndex];
    }
    if (position.x > originPosition.x + 100 || position.x < originPosition.x - 100) {
        isRight = !isRight;
    }

    if (isDown) {
        position.y += 9.81 * deltaTime;
    }
}

void Goomba::render() {
    if (!isDead) DrawTexture(texture, position.x, position.y, WHITE);
}

void Goomba::test() {
    if(IsKeyDown(KEY_A)) {
        accelerate(0.1f);
    }
    if (IsKeyDown(KEY_B)) {
        flipDirection();
    }
    if (IsKeyDown(KEY_C)) {
        hit();
    }
    if (IsKeyDown(KEY_D)) {
        resetSpeedY();
    }
    if (IsKeyDown(KEY_E)) {
        setDirection(slidingDirection::right);
    }
    if (IsKeyDown(KEY_F)) {
        setDirection(slidingDirection::down);
    }
    if (IsKeyDown(KEY_G)) {
        setDirection(slidingDirection::left);
    }  
}