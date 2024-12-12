#include "Enemy.hpp"

#include "raylib.h"

void Enemy::accelerate(float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void Enemy::flipDirection() {
    velocity.x *= -1;
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

//Goomba::Goomba(Vector2 position, float speed)
//     : Enemy(speed, 0.0f) {
//     this->originPosition = position;
//     this->position = position;
//     this->size = {16.0f, 16.0f};
//     this->textures.push_back(LoadTexture("assets/textures/Goomba_Walk1.png"));
//     this->textures.push_back(LoadTexture("assets/textures/Goomba_Walk2.png"));
//     this->animation = Animation(&textures[0], {1, 1}, 0.2f);
// }

// Goomba::~Goomba() {
//     for (auto& texture : textures) {
//         UnloadTexture(texture);
//     }
// }

// void Goomba::Update(float deltaTime) {
    
//     if (faceRight) {
//         position.x += 2* sin(deltaTime);
//         this->animation = Animation(&textures[0], {1, 1}, 0.2f);
//     } else {
//         position.x -= 2* sin(deltaTime);
//         this->animation = Animation(&textures[1], {1, 1}, 0.2f);
//     }
    
//     animation.Update(state, deltaTime, faceRight, fire, brake);
    
//     if (position.x >= originPosition.x + 100 || position.x <= originPosition.x - 100) {
//         faceRight = !faceRight;
//     }

//     // if (CheckCollisionRecs) ...
// }


// void Goomba::render() {
//     if (faceRight) DrawTexture(textures[0], position.x, position.y, WHITE);
//     else DrawTexture(textures[1], position.x, position.y, WHITE);
// }
// void Goomba::Attack() {
    
// }


// KoopaTroopa::KoopaTroopa(Vector2 position, float speed)
//     : Enemy(speed, 0.0f), isInShellMode(false) {
//     this->originPosition = position;
//     this->position = position;
//     this->size = {16.0f, 16.0f};
//     this->textures.push_back(LoadTexture("assets/textures/Koopa_Walk1.png"));
//     this->textures.push_back(LoadTexture("assets/textures/Koopa_Walk2.png"));
//     this->textures.push_back(LoadTexture("assets/textures/Koopa_Shell.png"));
//     this->animation = Animation(&textures[0], {1, 1}, 0.2f);
// }

// KoopaTroopa::~KoopaTroopa() {
//     for (auto& texture : textures) {
//         UnloadTexture(texture);
//     }
// }

// void KoopaTroopa::Update(float deltaTime) {
//     if (isInShellMode) {
//         position.x += 2 * speed * deltaTime;
//         this->animation = Animation(&textures[2], {1, 1}, 0.2f);
//     } else if (faceRight) {
//         position.x += 3 * sin(deltaTime);
//     }
//     else position.x -= 3 * sin(deltaTime);
//     animation.Update(state, deltaTime, faceRight, fire, brake);

//     if (position.x >= originPosition.x + 100 || position.x <= originPosition.x - 100) {
//         faceRight = !faceRight;
//     }
// }

// void KoopaTroopa::render() {
//     if(isInShellMode) DrawTexture(textures[2], position.x, position.y, WHITE);
//     else if (faceRight) DrawTexture(textures[0], position.x, position.y, WHITE);
//     else DrawTexture(textures[1], position.x, position.y, WHITE);
// }
// void KoopaTroopa::Attack() {
// }

// void KoopaTroopa::EnterShellMode() {
//     isInShellMode = true;
//     speed *= 2.0f;
// }


// // PiranhaPlant::PiranhaPlant(Vector2 position)
// //     : Enemy(0.0f, 0.0f) {
// //     this->position = position;
// //     this->size = {16.0f, 24.0f};
// //     this->textures.push_back(LoadTexture("resources/piranha.png"));
// //     this->animation = Animation(&textures[0], {2, 1}, 0.5f);
// // }

// // PiranhaPlant::~PiranhaPlant() {
// //     for (auto& texture : textures) {
// //         UnloadTexture(texture);
// //     }
// // }

// // void PiranhaPlant::Update(float deltaTime) {
// //     animation.Update(state, deltaTime, faceRight, fire, brake);
// // }

// // void PiranhaPlant::Attack() {
// //     //std::cout << "Piranha Plant attacks by biting the player!" << std::endl;
// // }

