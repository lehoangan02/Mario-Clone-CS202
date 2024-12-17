#include "Enemy.hpp"

#include "raylib.h"


EnemyFactory& EnemyFactory::GetEnemyFactory()
{
    static EnemyFactory Factory;
    return Factory;
}
Enemy* EnemyFactory::CreateEnemy(EnemyType type, Vector2 position, float leftBound, float rightBound)
{
    switch (type)
    {
        case EnemyType::GOOMBA:
        {
            Goomba* goomba = new Goomba(position);
            goomba->setBoundLR(leftBound, rightBound);
            return goomba;
        }
        case EnemyType::KOOPA_TROOPA:
        {
            KoopaTroopa* koopa = new KoopaTroopa(position);
            koopa->setBoundLR(leftBound, rightBound);
            return koopa;
        }
        case EnemyType::PIRANHA_PLANT:
        {
            PiranhaPlant* piranha = new PiranhaPlant(position);
            piranha->setBoundLR(leftBound, rightBound);
            return piranha;
        }
        case EnemyType::INVERSE_PIRANHA_PLANT:
        {
            InversePiranhaPlant* inversePiranha = new InversePiranhaPlant(position);
            inversePiranha->setBoundLR(leftBound, rightBound);
            return inversePiranha;
        }
        case EnemyType::SHY_GUY:
        {
            ShyGuy* shyGuy = new ShyGuy(position);
            shyGuy->setBoundLR(leftBound, rightBound);
            return shyGuy;
        }
        case EnemyType::LAKITU:
        {
            Lakitu* lakitu = new Lakitu(position);
            lakitu->setBoundLR(leftBound, rightBound);
            return lakitu;
        }
    }
    return nullptr; 
}



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
    size = { 60, 60 };
    speed = { 140, 0 };
    isRight = false;
    isDown = false;
    isDead = false;
    isDying = false;
    isCollisionTrue = false;

    setBound(0, 1024, 0, 768);
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
    
    setBound(0, 1024, 0, 768);
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
    if (!isDead) DrawTextureEx(texture, position, 0.0f, size.x/16, RAYWHITE);
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

    size = { 64, 132 };
    speed = { 0, 60};
    isRight = false;
    isDown = false;
    isDead = false;
    isPauseCollision = false;

    heightInGround = 0;
    setBound(0, 1024, 0, 768);
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
    setBound(0, 1024, 0, 768);
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
        DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, RAYWHITE);
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

        DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, RAYWHITE);
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

    size = { 63, 87 };
    speed = { 25, 0 };
    isRight = false;
    isDown = false;
    isDead = false;
    isCollisionTrue = false;
    setBound(0, 1024, 0, 768);
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
    setBound(0, 1024, 0, 768);
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
    setBound(leftBound, rightBound, topBound, bottomBound);
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


KoopaTroopa::KoopaTroopa(Vector2 position) : Enemy(position) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/Koopa_Walk1.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/Koopa_Walk1.png"));
    textures.push_back(LoadTexture("assets/textures/Koopa_Walk2.png"));
    textures.push_back(LoadTexture("assets/textures/Koopa_Shell.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);

    size = { 72, 108 };
    speed = { 140, 0 };
    shellSpeed = { 280, 0 };

    isRight = false;
    isDown = false;
    isDead = false;
    isCollisionTrue = false;
    isShell = false;
    setBound(0, 1024, 0, 768);
}

KoopaTroopa::KoopaTroopa(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position,size,speed) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/Koopa_Walk1.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/Koopa_Walk1.png"));
    textures.push_back(LoadTexture("assets/textures/Koopa_Walk2.png"));
    textures.push_back(LoadTexture("assets/textures/Koopa_Shell.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);

    shellSpeed.x = 2 * speed.x;
    shellSpeed.y = 2 * speed.y;

    isRight = false;
    isDown = false;
    isDead = false;
    isCollisionTrue = false;
    isShell = false;
    setBound(0, 1024, 0, 768);
}

KoopaTroopa::KoopaTroopa(Vector2 position, Vector2 size, Vector2 speed, float leftBound, float rightBound, float topBound, float bottomBound) : Enemy(position,size,speed,leftBound,rightBound,topBound,bottomBound) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/Koopa_Walk1.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/Koopa_Walk1.png"));
    textures.push_back(LoadTexture("assets/textures/Koopa_Walk2.png"));
    textures.push_back(LoadTexture("assets/textures/Koopa_Shell.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);

    isRight = false;
    isDown = false;
    isDead = false;
    isCollisionTrue = false;
    isShell = false;
    setBound(leftBound, rightBound, topBound, bottomBound);
}

void KoopaTroopa::hit() {
    if (isCollisionTrue) {
        isShell = true;
    }
}

void KoopaTroopa::update(float deltaTime) {
    if (isDead) return;

    if (isShell) {
        if (isRight) {
            position.x += shellSpeed.x * deltaTime;
        } else {
            position.x -= shellSpeed.x * deltaTime;
        }
    } else {
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

void KoopaTroopa::render() {
    if (!isDead) {
        if (isShell) {
            DrawTextureEx(textures[2], position, 0.0f, size.x/16, RAYWHITE);
        } else  if (isRight == false) {
            DrawTextureEx(texture, position, 0.0f, size.x/16, RAYWHITE);
        }
        else {
            Rectangle sourceRec = { 0, 0, -(float)texture.width, (float)texture.height }; 
            Rectangle destRec = { position.x, position.y, size.x, size.y };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, RAYWHITE);
        }
    }
}


Projectile::Projectile(Vector2 position) : Enemy(position) {
    this->position = position;
    this->originPosition = position;
    
    this->texture = LoadTexture("assets/textures/Projectile1.png");
    textures.push_back(LoadTexture("assets/textures/Projectile1.png"));
    textures.push_back(LoadTexture("assets/textures/Projectile2.png"));

    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);

    size = { 66, 70 };
    this->speed = {50, 17};
    active = true;
}

void Projectile::update(float deltaTime) {
    if (active) {
        if (!isRight && speed.x > 0) speed.x *= -1;

        speed.y += 9.81f * deltaTime;
        
        position.x += speed.x * deltaTime;
       
        position.y += speed.y * deltaTime;

        timer += deltaTime;
        if (timer >= animationTime) {
            timer -= animationTime;
            currentTextureIndex = (currentTextureIndex + 1) % 2;
            texture = textures[currentTextureIndex];
        }
    }


}



void Projectile::render() {
    if (active) {
        DrawTextureEx(texture, position, 0.0f, 1.0f, RAYWHITE);
    }
}


void Projectile::hit() {
    if (isCollisionTrue) {
        active = false;
    }
}

void Projectile::setActivate(bool newActive) {
    active = newActive;
}

void Projectile::deactivate() {
    active = false;
}

bool Projectile::isActive() {
    return active;
}

void Projectile::setRight(bool isRight) {
    this->isRight = isRight;
}

Lakitu::Lakitu(Vector2 position) : Enemy(position) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/Lakitu1.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/Lakitu1.png"));
    textures.push_back(LoadTexture("assets/textures/Lakitu2.png"));
    textures.push_back(LoadTexture("assets/textures/Lakitu3.png"));
    textures.push_back(LoadTexture("assets/textures/Lakitu4.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);

    size = { 72, 108 };
    speed = { 25, 0 };
    shootTime = 6.0f;
    curentTimer = 0.0f;

    setBound(0, 1024, 0, 768);
}

Lakitu::Lakitu(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position,size,speed) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/Lakitu1.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/Lakitu1.png"));
    textures.push_back(LoadTexture("assets/textures/Lakitu2.png"));
    textures.push_back(LoadTexture("assets/textures/Lakitu3.png"));
    textures.push_back(LoadTexture("assets/textures/Lakitu4.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);

    shootTime = 6.0f;
    curentTimer = 0.0f;

    setBound(0, 1024, 0, 768);
}

Lakitu::Lakitu(Vector2 position, Vector2 size, Vector2 speed, float leftBound, float rightBound, float topBound, float bottomBound) : Enemy(position,size,speed,leftBound,rightBound,topBound,bottomBound) {
    this->position = position;
    this->originPosition = position;
    
    texture = LoadTexture("assets/textures/Lakitu1.png");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(LoadTexture("assets/textures/Lakitu1.png"));
    textures.push_back(LoadTexture("assets/textures/Lakitu2.png"));
    textures.push_back(LoadTexture("assets/textures/Lakitu3.png"));
    textures.push_back(LoadTexture("assets/textures/Lakitu4.png"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);

    shootTime = 6.0f;
    curentTimer = 0.0f;

    setBound(leftBound, rightBound, topBound, bottomBound);
}

void Lakitu::hit() {
    if (isCollisionTrue) {
        isDead = true;
    }
}

void Lakitu::update(float deltaTime) {
    if (isDead) return;

    if (isRight) {
        position.x += speed.x * deltaTime;
    } else {
        position.x -= speed.x * deltaTime;
    }

    timer += deltaTime;
    if (timer >= animationTime) {
        timer -= animationTime;
        currentTextureIndex = (currentTextureIndex + 1) % 3;
        texture = textures[currentTextureIndex];
    }

    curentTimer += deltaTime;
    if (curentTimer >= shootTime) {
        curentTimer -= shootTime;
        projectiles.push_back(std::make_shared<Projectile>(Projectile{position}));
        projectiles.back()->setRight(isRight);
        isShoot = true;
    }
    else {
        isShoot = false;
    }

    for (auto& projectile : projectiles) {
        projectile->update(deltaTime);
    }

    if (position.x < leftBound || position.x + size.x > rightBound) {
        isRight = !isRight;
    }
}

void Lakitu::render() {
    if (!isDead) {
        if (isRight == false) {
            if (!isShoot) DrawTextureEx(texture, position, 0.0f, size.x/60, RAYWHITE);
            else DrawTextureEx(textures[3], position, 0.0f, size.x/60, RAYWHITE);
        }
        else {
            Rectangle sourceRec = { 0, 0, -(float)texture.width, (float)texture.height }; 
            Rectangle destRec = { position.x, position.y, size.x, size.y };
            Vector2 origin = { 0.0f, 0.0f };
            if (!isShoot) DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, RAYWHITE);
            else DrawTexturePro(textures[3], sourceRec, destRec, origin, 0.0f, RAYWHITE);
        }
    }

    for (auto& projectile : projectiles) {
        projectile->render();
    }
}
