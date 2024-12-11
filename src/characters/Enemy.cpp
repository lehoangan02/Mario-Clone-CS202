#include "Enemy.hpp"
#include "enemy.hpp"
#include "raylib.h"

Enemy::Enemy(float speed, float jumpHeight)
    : Character(jumpHeight), speed(speed), isAttacking(false) {}

Enemy::~Enemy() {}

Goomba::Goomba(Vector2 position, float speed)
    : Enemy(speed, 0.0f) { 
    this->originPosition = position;
    this->position = position;
    this->size = {20.0f, 20.0f}; 
    this->textures.push_back(LoadTexture("assets/textures/Goomba_Walk1.png"));
    this->textures.push_back(LoadTexture("assets/textures/Goomba_Walk2.png"));
    this->animation = Animation(&textures[0], {1, 1}, 0.2f); 
}

Goomba::~Goomba() {
    for (auto& texture : textures) {
        UnloadTexture(texture);
    }
}

void Goomba::Update(float deltaTime) {
    
    if (faceRight) {
        position.x += 2* sin(deltaTime);
        this->animation = Animation(&textures[0], {1, 1}, 0.2f); 
    } else {
        position.x -= 2* sin(deltaTime);
        this->animation = Animation(&textures[1], {1, 1}, 0.2f);  
    }
    
    animation.Update(state, deltaTime, faceRight, fire, brake);
    
    if (position.x >= originPosition.x + 100 || position.x <= originPosition.x - 100) {
        faceRight = !faceRight; 
    }

    // if (CheckCollisionRecs) ...
}


void Goomba::render() {
    DrawTexture(textures[0], position.x, position.y, WHITE);
}
void Goomba::Attack() {
    
}


KoopaTroopa::KoopaTroopa(Vector2 position, float speed)
    : Enemy(speed, 0.0f), isInShellMode(false) {
    this->position = position;
    this->size = {16.0f, 16.0f}; 
    this->textures.push_back(LoadTexture("resources/koopa.png"));
    this->animation = Animation(&textures[0], {4, 1}, 0.2f);
}

KoopaTroopa::~KoopaTroopa() {
    for (auto& texture : textures) {
        UnloadTexture(texture);
    }
}

void KoopaTroopa::Update(float deltaTime) {
    if (isInShellMode) {
        position.x += 2 * speed * deltaTime; 
    } else {
        position.x += speed * deltaTime;
    }
    animation.Update(state, deltaTime, faceRight, fire, brake);
}

void KoopaTroopa::Attack() {
    //std::cout << "Koopa Troopa attacks by sliding in shell mode!" << std::endl;
}

void KoopaTroopa::EnterShellMode() {
    isInShellMode = true;
    speed *= 2.0f; 
}


// PiranhaPlant::PiranhaPlant(Vector2 position)
//     : Enemy(0.0f, 0.0f) { 
//     this->position = position;
//     this->size = {16.0f, 24.0f}; 
//     this->textures.push_back(LoadTexture("resources/piranha.png"));
//     this->animation = Animation(&textures[0], {2, 1}, 0.5f); 
// }

// PiranhaPlant::~PiranhaPlant() {
//     for (auto& texture : textures) {
//         UnloadTexture(texture);
//     }
// }

// void PiranhaPlant::Update(float deltaTime) {
//     animation.Update(state, deltaTime, faceRight, fire, brake);
// }

// void PiranhaPlant::Attack() {
//     //std::cout << "Piranha Plant attacks by biting the player!" << std::endl;
// }
