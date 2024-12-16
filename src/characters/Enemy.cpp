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
    
    texture = LoadTexture("assets/textures/Goomba_Walk1.png");
    textures.push_back(LoadTexture("assets/textures/Goomba_Walk1.png"));
    textures.push_back(LoadTexture("assets/textures/Goomba_Walk2.png"));
    textures.push_back(LoadTexture("assets/textures/Goomba_Flat.png"));

    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);

    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    size = { 16, 16 };
    speed = { 40, 0 };
    isRight = false;
    isDown = false;
    isDead = false;
    isDying = false;
    isCollisionTrue = false;
}

Goomba::Goomba(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/Goomba_Walk1.png");
    textures.push_back(LoadTexture("assets/textures/Goomba_Walk1.png"));
    textures.push_back(LoadTexture("assets/textures/Goomba_Walk2.png"));
    textures.push_back(LoadTexture("assets/textures/Goomba_Flat.png"));

    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);

    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);

    this->size = size;
    this->speed = speed;
    isRight = false;
    isDown = false;
    isDead = false;
    isDying = false;
    isCollisionTrue = false;
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
    if (position.x < leftBound || position.x + texture.width * size.x/16 > rightBound) {
        isRight = !isRight;
    }
    if (position.y + size.y> bottomBound) {
        isDown = false;
    }

    if (isDown) {
        position.y += 9.81 * deltaTime;
    }
}

void Goomba::render() {
    if (!isDead) DrawTextureEx(texture, position, 0.0f, size.x/16, WHITE);
}


PiranhaPlant::PiranhaPlant(Vector2 position) : Enemy(position) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/PiranhaPlant_0.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/PiranhaPlant_0.png"));
    textures.push_back(LoadTexture("assets/textures/PiranhaPlant_1.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);

    size = { 32, 66 };
    speed = { 0, 10};
    isRight = false;
    isDown = false;
    isDead = false;
    isPauseCollision = false;

    heightInGround = 0;
    topBound = size.y + position.y;
    bottomBound = position.y;
}

PiranhaPlant::PiranhaPlant(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position, size, speed) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/PiranhaPlant_0.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/PiranhaPlant_0.png"));
    textures.push_back(LoadTexture("assets/textures/PiranhaPlant_1.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);

    isRight = false;
    isDown = false;
    isDead = false;
    isPauseCollision = false;

    heightInGround = 0;
    topBound = size.y + position.y;
    bottomBound = position.y;
}
void PiranhaPlant::update(float deltaTime) {
    if (isDead) return;

    if (!isPauseCollision) {
            timer += deltaTime;
        if (timer >= animationTime) {
            timer -= animationTime; 
            currentTextureIndex = (currentTextureIndex + 1) % 2; 
            texture = textures[currentTextureIndex];
        }

        if(isDown) {
            position.y += speed.y * deltaTime;
            heightInGround += speed.y * deltaTime;
        }
        else {
            position.y -= speed.y * deltaTime;
            heightInGround -= speed.y * deltaTime;
        }
        if(position.y > topBound|| position.y < bottomBound ) {
            isDown = !isDown;
        }

        heightInGround = Clamp(heightInGround, 0.0f, size.y);
    }
    else {
        timer += deltaTime;
        if (timer >= 6 * animationTime) {
            timer -= 6 * animationTime; 
            isPauseCollision = false;
        }
    }
}

void PiranhaPlant::render() {
    if (!isDead) {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height - heightInGround/size.y * 66};
        Rectangle destRec = { position.x, position.y, size.x, size.y - heightInGround};
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
    }
}

void PiranhaPlant::hit() {
    isDead = true;
}


InversePiranhaPlant::InversePiranhaPlant(Vector2 position) : PiranhaPlant(position) {
    heightInGround = 66;
    topBound = position.y + 66;
    bottomBound = position.y;
}

InversePiranhaPlant::InversePiranhaPlant(Vector2 position, Vector2 size, Vector2 speed) : PiranhaPlant(position, size, speed) {
    heightInGround = size.y;
    topBound = position.y + size.y;
    bottomBound = position.y;
    isDown = true;
}
void InversePiranhaPlant::update(float deltaTime) {
    if (isDead) return;

    if (!isPauseCollision) {
        timer += deltaTime;
        if (timer >= animationTime) {
            timer -= animationTime;
            currentTextureIndex = (currentTextureIndex + 1) % 2;
            texture = textures[currentTextureIndex];
        }

        if (isDown) {
            position.y += speed.y * deltaTime; 
            heightInGround -= speed.y * deltaTime; 
        } else {
            position.y -= speed.y * deltaTime; 
            heightInGround += speed.y * deltaTime; 
        }
        if (position.y <= bottomBound || position.y >= topBound) {
            isDown = !isDown;
        }
    } else {
        timer += deltaTime;
        if (timer >= 6 * animationTime) {
            timer -= 6 * animationTime;
            isPauseCollision = false;
        }
    }
}


void InversePiranhaPlant::render() {
    if (!isDead) {
        Rectangle sourceRec = { 
            0.0f, 
            0.0f, 
            (float)texture.width, 
            -((float)texture.height - heightInGround/size.y * 66)
        };

        Rectangle destRec = { 
            originPosition.x, 
            originPosition.y, 
            size.x, 
            size.y - heightInGround
        };

        Vector2 origin = {0.0f, 0.0f };

        DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
    }
}

void InversePiranhaPlant::test() {
    if (IsKeyDown(KEY_A)) {
        setIsPauseCollision(true);
    }
}

ShyGuy::ShyGuy(Vector2 position) : Enemy(position) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/ShyGuy1.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/ShyGuy1.png"));
    textures.push_back(LoadTexture("assets/textures/ShyGuy2.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);

    size = { 21, 29 };
    speed = { 10, 0 };
    isRight = false;
    isDown = false;
    isDead = false;
    isCollisionTrue = false;
}

ShyGuy::ShyGuy(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position,size,speed) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/ShyGuy1.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/ShyGuy1.png"));
    textures.push_back(LoadTexture("assets/textures/ShyGuy2.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);

    isRight = false;
    isDown = false;
    isDead = false;
    isCollisionTrue = false;
}

ShyGuy::ShyGuy(Vector2 position, Vector2 size, Vector2 speed, float leftBound, float rightBound, float topBound, float bottomBound) : Enemy(position,size,speed,leftBound,rightBound,topBound,bottomBound) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/ShyGuy1.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/ShyGuy1.png"));
    textures.push_back(LoadTexture("assets/textures/ShyGuy2.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);

    isRight = false;
    isDown = false;
    isDead = false;
    isCollisionTrue = false;
}

void ShyGuy::hit() {
    if (isCollisionTrue) {
        isDead = true;
    }
}

void ShyGuy::update(float deltaTime) {
    if (isDead) return;

    if (isRight) {
        position.x += speed.x * deltaTime;
    } else {
        position.x -= speed.x * deltaTime;
    }

    timer += deltaTime;
    if (timer >= animationTime) {
        timer -= animationTime;
        currentTextureIndex = (currentTextureIndex + 1) % 2;
        texture = textures[currentTextureIndex];
    }

    if (position.x < leftBound) {
        isRight = true;
    }
    if (position.x + size.x > rightBound) {
        isRight = false;
    }

    if (position.y <= topBound) {
        isDown = true;
    }

    if (position.y + size.y >= bottomBound) {
        isDown = false;
    }
}

void ShyGuy::render() {
    if (!isDead) {
        if (isRight == false) {
            DrawTextureEx(texture, position, 0.0f, size.x/21, WHITE);
        } else {
            Rectangle sourceRec = { 0, 0, -(float)texture.width, (float)texture.height }; 
            Rectangle destRec = { position.x, position.y, size.x, size.y };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
        }
    }
}

