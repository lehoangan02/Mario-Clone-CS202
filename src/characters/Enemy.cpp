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

void Enemy::setBound(float left, float right, float top, float bottom) {
        leftBound = left;
        rightBound = right;
        topBound = top;
        bottomBound = bottom;
    }

void Enemy::render() {
    DrawTexture(texture, position.x, position.y, WHITE);
}

Goomba::Goomba(Vector2 position) : Enemy(position) {
    this->position = position;
    this->originPosition = position;

    Image image = LoadImage("assets/textures/Goomba_Walk1.png");

    ImageResize(&image, 60, 60);

    texture = LoadTextureFromImage(image);
    textures.push_back(LoadTextureFromImage(image));

    image = LoadImage("assets/textures/Goomba_Walk2.png");
    ImageResize(&image, 60, 60);
    textures.push_back(LoadTextureFromImage(image));

    image = LoadImage("assets/textures/Goomba_Flat.png");
    ImageResize(&image, 60, 60);
    textures.push_back(LoadTextureFromImage(image));

    UnloadImage(image);
    size = { 60, 60 };
    speed = { 40, 0 };
    isRight = false;
    isDown = false;
    isDead = false;
    isDying = false;
}

Goomba::Goomba(Vector2 position, Vector2 size, Vector2 speed) {
    this->position = position;
    this->originPosition = position;

    Image image = LoadImage("assets/textures/Goomba_Walk1.png");

    ImageResize(&image, size.x, size.y);

    texture = LoadTextureFromImage(image);
    textures.push_back(LoadTextureFromImage(image));

    image = LoadImage("assets/textures/Goomba_Walk2.png");
    ImageResize(&image, size.x, size.y);
    textures.push_back(LoadTextureFromImage(image));

    image = LoadImage("assets/textures/Goomba_Flat.png");
    ImageResize(&image, size.x, size.y);
    textures.push_back(LoadTextureFromImage(image));

    UnloadImage(image);
    this->size = size;
    this->speed = speed;
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
    if (position.x < leftBound || position.x + texture.width > rightBound) {
        isRight = !isRight;
    }
    if (position.y > bottomBound) {
        isDown = false;
    }

    if (isDown) {
        position.y += 9.81 * deltaTime;
    }
}

void Goomba::render() {
    if (!isDead) DrawTextureEx(texture, position, 0.0f, 1.0f, WHITE);
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