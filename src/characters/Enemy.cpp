#include "Enemy.hpp"

#include "raylib.h"
#include "../ResourceManager.hpp"


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
    
    texture = ResourceManager::GetInstance()->GetTexture("goomba1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
    textures.push_back(ResourceManager::GetInstance()->GetTexture("goomba1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("goomba2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("goomba3"));
    

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

    setBound(0, 1024, 0, 768);
}

Goomba::Goomba(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position) {
    this->position = position;
    this->originPosition = position;
    
    texture = ResourceManager::GetInstance()->GetTexture("goomba1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
    textures.push_back(ResourceManager::GetInstance()->GetTexture("goomba1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("goomba2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("goomba3"));

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
    
    setBound(0, 1024, 0, 768);
}
void Goomba::hit() {
    this->texture = textures[2];           
    isDying = true;              
    dyingTime = 0.0f; 
}
  

void Goomba::update(float deltaTime) {
    if (isDying) {
        dyingTime += deltaTime;
        if (dyingTime >= 0.2f) {
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
        if (position.x < leftBound) {
            position.x = leftBound;
            isRight = true;
        }
        if (position.x + texture.width * size.x/16 > rightBound) {
            position.x = rightBound - texture.width * size.x/16;
            isRight = false;
        }
        // isRight = !isRight;
    }
    if (position.y + size.y> bottomBound) {
        position.y = bottomBound - size.y;
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
    
    texture = ResourceManager::GetInstance()->GetTexture("piranha1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("piranha1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("piranha2"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);

    size = { 64, 132 };
    speed = { 0, 60};
    isRight = false;
    isDown = false;
    isDead = false;

    heightInGround = 0;
    setBound(0, 1024, 0, 768);
    topBound = size.y + position.y;
    bottomBound = position.y;
}

PiranhaPlant::PiranhaPlant(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position, size, speed) {
    this->position = position;
    this->originPosition = position;
    
    texture = ResourceManager::GetInstance()->GetTexture("piranha1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("piranha1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("piranha2"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);

    isRight = false;
    isDown = false;
    isDead = false;

    heightInGround = 0;
    setBound(0, 1024, 0, 768);
    topBound = size.y + position.y;
    bottomBound = position.y;
}
void PiranhaPlant::update(float deltaTime) {
    if (isDead) return;
    if (isDying) {
        isDown = true;
        speed.y *= 1.1f;
    }
    if (isDying && heightInGround >= size.y) {
        isDead = true;
        isDying = false;
    }

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
        if (position.y > topBound) {
            position.y = topBound;
            isDown = false;
        }
        if (position.y < bottomBound) {
            position.y = bottomBound;
            isDown = true;
        }
    }

    heightInGround = Clamp(heightInGround, 0.0f, size.y);
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
    isDying = true;
    dyingTime = 0.0f;
}


InversePiranhaPlant::InversePiranhaPlant(Vector2 position) : PiranhaPlant(position) {
    heightInGround = size.y;
    topBound = position.y + size.y;
    bottomBound = position.y;
    isDown = true;;
}

InversePiranhaPlant::InversePiranhaPlant(Vector2 position, Vector2 size, Vector2 speed) : PiranhaPlant(position, size, speed) {
    heightInGround = size.y;
    topBound = position.y + size.y;
    bottomBound = position.y;
    isDown = true;
}
void InversePiranhaPlant::update(float deltaTime) {
    if (isDead) return;
    if (isDying) {
        isDown = false;
        speed.y *= 1.1f;
    }
    if (isDying && heightInGround >= size.y) {
        isDead = true;
        isDying = false;
    }
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
        if (position.y <= bottomBound) {
            position.y = bottomBound;
        }
        if (position.y >= topBound) {
            position.y = topBound;
        }
        isDown = !isDown;
    }
    heightInGround = Clamp(heightInGround, 0.0f, size.y);
   
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
    
    texture = ResourceManager::GetInstance()->GetTexture("shyguy1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy4"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy5"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy6"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[4], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[5], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[4], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[5], TEXTURE_WRAP_CLAMP);

    size = { 40, 40 };
    speed = { 130, 0 };
    isRight = false;
    isDown = false;
    isDead = false;
    setBound(0, 1024, 0, 768);
}

ShyGuy::ShyGuy(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position,size,speed) {
    this->position = position;
    this->originPosition = position;
    
    texture = ResourceManager::GetInstance()->GetTexture("shyguy1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy4"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy5"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy6"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[4], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[5], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[4], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[5], TEXTURE_WRAP_CLAMP);

    isRight = false;
    isDown = false;
    isDead = false;
    setBound(0, 1024, 0, 768);
}

ShyGuy::ShyGuy(Vector2 position, Vector2 size, Vector2 speed, float leftBound, float rightBound, float topBound, float bottomBound) : Enemy(position,size,speed,leftBound,rightBound,topBound,bottomBound) {
    this->position = position;
    this->originPosition = position;
    
    texture = ResourceManager::GetInstance()->GetTexture("shyguy1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy4"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy5"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("shyguy6"));
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[4], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[5], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[4], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[5], TEXTURE_WRAP_CLAMP);

    isRight = false;
    isDown = false;
    isDead = false;
    setBound(leftBound, rightBound, topBound, bottomBound);
}

void ShyGuy::hit() {
    isDying = true;
    isBouncing = true;
    bounceTime = 0.15f; 
    fallSpeed = -200.0f;
}

void ShyGuy::update(float deltaTime) {
    if (isDead) return;

    if (isDying) {
        if (isBouncing) {
            bounceTime -= deltaTime;
            position.y += fallSpeed * deltaTime;
            if (bounceTime <= 0.0f) {
                isBouncing = false;
                fallSpeed = 0.0f;
            }
        } 
        else {
            fallSpeed += 981.0f*3 * deltaTime; 
            position.y += fallSpeed * deltaTime;
            if (position.y > bottomBound) {
                isDead = true;
                isDying = false;
            }
        }
    } 
    else {
        if (isRight) {
            position.x += speed.x * deltaTime;
        } else {
            position.x -= speed.x * deltaTime;
        }

        timer += deltaTime;
        if (timer >= animationTime) {
            timer -= animationTime;
            currentTextureIndex = (currentTextureIndex + 1) % 6;
            texture = textures[currentTextureIndex];
        }

        if (position.x < leftBound) {
            position.x = leftBound;
            isRight = true;
        }
        if (position.x + size.x * 1.5f > rightBound) {
            position.x = rightBound - size.x * 1.5f;
            isRight = false;
        }

        if (position.y <= topBound) {
            position.y = topBound;
            isDown = true;
        }

        if (position.y + size.y * 1.5f >= bottomBound) {
            position.y = bottomBound - size.y * 1.5f;
            isDown = false;
        }
    }
}

void ShyGuy::render() {
    if (!isDead) {
        if (isRight == false) {
            DrawTextureEx(texture, position, 0.0f, 2.0f, RAYWHITE);
        } else {
            Rectangle sourceRec = { 0, 0, -(float)texture.width, (float)texture.height }; 
            Rectangle destRec = { position.x, position.y, size.x * 2.0f, size.y * 2.0f };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, RAYWHITE);
        }
    }
}


KoopaTroopa::KoopaTroopa(Vector2 position) : Enemy(position) {
    this->position = position;
    this->originPosition = position;

    texture = ResourceManager::GetInstance()->GetTexture("koopa1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa4"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa5"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa6"));

    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[4], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[5], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[4], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[5], TEXTURE_WRAP_CLAMP);

    size = { 72, 108 };
    speed = { 140, 0 };
    shellSpeed = { 280, 0 };

    isRight = false;
    isDown = false;
    isDead = false;
    isShell = false;
    setBound(0, 1024, 0, 768);

    fallSpeed = 0.0f;
    isBouncing = false;
    bounceTime = 0.0f;

}

KoopaTroopa::KoopaTroopa(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position,size,speed) {
    this->position = position;
    this->originPosition = position;
    
    texture = ResourceManager::GetInstance()->GetTexture("koopa1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa4"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa5"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa6"));

    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[4], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[5], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[4], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[5], TEXTURE_WRAP_CLAMP);

    shellSpeed.x = 2 * speed.x;
    shellSpeed.y = 2 * speed.y;

    isRight = false;
    isDown = false;
    isDead = false;
    isShell = false;
    setBound(0, 1024, 0, 768);

    fallSpeed = 0.0f;
    isBouncing = false;
    bounceTime = 0.0f;

}

KoopaTroopa::KoopaTroopa(Vector2 position, Vector2 size, Vector2 speed, float leftBound, float rightBound, float topBound, float bottomBound) : Enemy(position,size,speed,leftBound,rightBound,topBound,bottomBound) {
    this->position = position;
    this->originPosition = position;
    
    texture = ResourceManager::GetInstance()->GetTexture("koopa1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa4"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa5"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("koopa6"));;

    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[4], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[5], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[4], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[5], TEXTURE_WRAP_CLAMP);

    isRight = false;
    isDown = false;
    isDead = false;
    isShell = false;
    setBound(leftBound, rightBound, topBound, bottomBound);

    fallSpeed = 0.0f;
    isBouncing = false;
    bounceTime = 0.0f;
}

void KoopaTroopa::hit() {
    if (isShell) {
        isDying = true;
        isBouncing = true;
        bounceTime = 0.15f; 
        fallSpeed = -200.0f; 
    } 
    else {
        isShell = true;
        shellSpeed.x = 2 * speed.x;
        shellSpeed.y = 2 * speed.y;
    }
}

void KoopaTroopa::update(float deltaTime) {
    if (isDead) return;
    
    if (isDying) {
        if (isBouncing) {
            bounceTime -= deltaTime;
            position.y += fallSpeed * deltaTime;
            if (bounceTime <= 0.0f) {
                isBouncing = false;
                fallSpeed = 0.0f;
            }
        } 
        else {
            fallSpeed += 981.0f*3 * deltaTime; 
            position.y += fallSpeed * deltaTime;
            if (position.y > bottomBound) {
                position.y = bottomBound;
                isDead = true;
                isDying = false;
            }
        }
    } 
    else {
        if (isShell) {
            if (isRight) {
                position.x += shellSpeed.x * deltaTime;
            } else {
                position.x -= shellSpeed.x * deltaTime;
            }
            if (position.x <= leftBound || position.x + texture.width * 6.0f >= rightBound) {
                if (position.x < leftBound) {
                    position.x = leftBound;
                }
                if (position.x + texture.width * 6.0f > rightBound) {
                    position.x = rightBound - texture.width * 6.0f;
                }
                isRight = !isRight;
            }

            timer += deltaTime;
            if (timer >= animationTime) {
                timer -= animationTime;
                currentTextureIndex = 3 + ((currentTextureIndex + 1) % 3);
                texture = textures[currentTextureIndex];
            }
        } 
        else if (!isShell){
            if (isRight) {
                position.x += speed.x * deltaTime;
            } 
            else {
                position.x -= speed.x * deltaTime;
            }

            timer += deltaTime;
            if (timer >= animationTime) {
                timer -= animationTime;
                currentTextureIndex = (currentTextureIndex + 1) % 3;
                texture = textures[currentTextureIndex];
            }
            if (position.x <= leftBound || position.x + texture.width * 4.0f >= rightBound) {
                if (position.x < leftBound) {
                    position.x = leftBound;
                }
                if (position.x + texture.width * 4.0f > rightBound) {
                    position.x = rightBound - texture.width * 4.0f;
                }
                isRight = !isRight;
            }
        }
    }
}

void KoopaTroopa::render() {
    if (!isDead ) {
        if ((isShell) || isDying) {
            DrawTextureEx(texture, position, 0.0f, 6.0f, RAYWHITE);
        } else  if (isRight == true) {
            DrawTextureEx(texture, position, 0.0f, 4.0f, RAYWHITE);
        }
        else {
            Rectangle sourceRec = { 0, 0, -(float)texture.width, (float)texture.height }; 
            Rectangle destRec = { position.x, position.y, texture.width * 4.0f, texture.height * 4.0f };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, RAYWHITE);
        }
    }
}


Projectile::Projectile(Vector2 position) : Enemy(position) {
    this->position = position;
    this->originPosition = position;
    
    this->texture = ResourceManager::GetInstance()->GetTexture("bullet1");
    textures.push_back(ResourceManager::GetInstance()->GetTexture("bullet1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("bullet2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("bullet3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("bullet4"));

    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[1], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[2], TEXTURE_FILTER_POINT);
    SetTextureFilter(textures[3], TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(textures[3], TEXTURE_WRAP_CLAMP);

    size = { 66, 70 };
    this->speed = {220, 153};
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
            currentTextureIndex = (currentTextureIndex + 1) % 3;
            texture = textures[currentTextureIndex];
        }
    }


}



void Projectile::render() {
    if (active) {
        DrawTextureEx(texture, position, 0.0f, 2.0f, RAYWHITE);
    }
}


void Projectile::hit() {
    active = false;
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
    
    texture = ResourceManager::GetInstance()->GetTexture("lakitu1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu4"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu5"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu6"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu7"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu8"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu9"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu10"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu11"));
    for (int i = 0; i< 10; i++) {
        SetTextureFilter(textures[i], TEXTURE_FILTER_POINT);
        SetTextureWrap(textures[i], TEXTURE_WRAP_CLAMP);
    }
    
    size = { 72, 108 };
    speed = { 150, 0 };
    shootTime = 2.2f;
    curentTimer = 0.0f;

    setBound(0, 1024, 0, 768);
    isDead = false;
}

Lakitu::Lakitu(Vector2 position, Vector2 size, Vector2 speed) : Enemy(position,size,speed) {
    this->position = position;
    this->originPosition = position;
    
    texture = ResourceManager::GetInstance()->GetTexture("lakitu1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu4"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu5"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu6"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu7"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu8"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu9"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu10"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu11"));
    for (int i = 0; i< 10; i++) {
        SetTextureFilter(textures[i], TEXTURE_FILTER_POINT);
        SetTextureWrap(textures[i], TEXTURE_WRAP_CLAMP);
    }

    shootTime = 6.0f;
    curentTimer = 0.0f;

    setBound(0, 1024, 0, 768);
    isDead = false;
}

Lakitu::Lakitu(Vector2 position, Vector2 size, Vector2 speed, float leftBound, float rightBound, float topBound, float bottomBound) : Enemy(position,size,speed,leftBound,rightBound,topBound,bottomBound) {
    this->position = position;
    this->originPosition = position;
    
    texture = ResourceManager::GetInstance()->GetTexture("lakitu1");
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu1"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu2"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu3"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu4"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu5"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu6"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu7"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu8"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu9"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu10"));
    textures.push_back(ResourceManager::GetInstance()->GetTexture("lakitu11"));
    for (int i = 0; i< 10; i++) {
        SetTextureFilter(textures[i], TEXTURE_FILTER_POINT);
        SetTextureWrap(textures[i], TEXTURE_WRAP_CLAMP);
    }

    shootTime = 10.0f;
    curentTimer = 0.0f;

    setBound(leftBound, rightBound, topBound, bottomBound);
    isDead = false;
}

void Lakitu::hit() {
    isDead = true;
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
        currentTextureIndex = (currentTextureIndex + 1) % 11;
        texture = textures[currentTextureIndex];
    }

    curentTimer += deltaTime;
    if (curentTimer >= shootTime) {
        curentTimer -= shootTime;
        if (isRight) 
            projectiles.push_back(std::make_shared<Projectile>(Projectile({position.x + texture.width * 1.6f, position.y})));
        else
            projectiles.push_back(std::make_shared<Projectile>(Projectile({position.x - 25.0f, position.y})));
        projectiles.back()->setRight(isRight);
        isShoot = true;
    }
    else {
        isShoot = false;
    }

    for (auto& projectile : projectiles) {
        projectile->update(deltaTime);
    }

    if (position.x <= leftBound || position.x + texture.width *2.0f>= rightBound) {
        if (position.x < leftBound) {
            position.x = leftBound;
        }
        if (position.x + texture.width * 2.0f > rightBound) {
            position.x = rightBound - texture.width * 2.0f;
        }
        isRight = !isRight;
    }
}

void Lakitu::render() {
    if (!isDead) {
        if (isRight == false) {
            if (!isShoot) DrawTextureEx(texture, position, 0.0f, 2.0f, RAYWHITE);
            else DrawTextureEx(textures[10], position, 0.0f, 2.0f, RAYWHITE);
        }
        else {
            Rectangle sourceRec = { 0, 0, -(float)texture.width, (float)texture.height }; 
            Rectangle destRec = { position.x, position.y, texture.width * 2.0f, texture.height * 2.0f };
            Vector2 origin = { 0.0f, 0.0f };
            if (!isShoot) DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, RAYWHITE);
            else DrawTexturePro(textures[10], sourceRec, destRec, origin, 0.0f, RAYWHITE);
        }
    }

    for (auto& projectile : projectiles) {
        projectile->render();
    }
}
