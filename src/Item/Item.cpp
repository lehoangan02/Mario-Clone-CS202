
#include "Item.h"
#include <iostream>
#include <math.h>


Item::Item(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, int totalFrames, float switchTime, Vector2 velocity, bool appeared)
    : startPosition(startPos), endPosition(endPos), size(size), texture(tex),
    totalFrames(totalFrames), switchTime(switchTime), velocity(velocity),
     elapsedTime(0), currentFrame(0), isReturning(false), APPEARED(appeared),
    Notify(false)    
{
    position = startPosition;
    frameSize = { (float)(tex.width / totalFrames), (float)tex.height }; 
    moves = 0;

    if (startPosition.x < endPosition.x) {
        this->velocity.x = fabs(this->velocity.x);
    }
    else if (startPosition.x > endPosition.x) {
        this->velocity.x = -fabs(this->velocity.x);
    }
    else {
        this->velocity.x = 0;
    }
    if (startPosition.y < endPosition.y) {
        this->velocity.y = fabs(this->velocity.y);
        
    }
    else if (startPosition.y > endPosition.y) {
        this->velocity.y = -fabs(this->velocity.y);
    }
    else {
        this->velocity.y = 0;
    }

    
}
Item::~Item() {
    UnloadTexture(texture);
}
float Item::norm(Vector2 vector1, Vector2 vector2) {
    float result = sqrt(pow(vector1.x - vector2.x, 2) +
        pow(vector1.y - vector2.y, 2));
    return result;
}
void Item::onNotify() {
    Notify = true;
}


void Item::Draw() {};
void Item::Update(float deltaTime) {};
Coin::Coin(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity)
    : Item(startPos, endPos, size, tex, COIN_FRAME_COUNT, COIN_FRAME_TIME, velocity, true) {}
Item* Item::Transform(Item* currentItem, const std::string& newItemType, Texture2D newTexture, int newTotalFrames, float newSwitchTime) {
    Vector2 position = currentItem->GetPosition();
    Vector2 size = currentItem->GetSize();
    Vector2 velocity = currentItem->velocity;
    Vector2 startPosition = currentItem->startPosition;
    Vector2 endPosition = currentItem->endPosition;

    delete currentItem;

    if (newItemType == "FireFlower") {
        return new FireFlower(startPosition, endPosition, size, newTexture, velocity);
    }
    

    return nullptr;
}
void Coin::applyEffect(Character* character) {
    return;
}
void Coin::Update(float deltaTime) { //acceleration
    if (Notify == true)
    {
        if (!APPEARED) {
            return;
        }
        elapsedTime += deltaTime;
        if (elapsedTime >= switchTime) {
            currentFrame = (currentFrame + 1) % totalFrames;
            elapsedTime = 0;
        }
        if (velocity.y > 0) velocity.y += 2.0f;
        else velocity.y -= 2.0f;
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        if (!isReturning) {
            if (fabs(position.x - endPosition.x) <= fabs(velocity.x * deltaTime) &&
                fabs(position.y - endPosition.y) <= fabs(velocity.y * deltaTime)) {
                position = endPosition;
                isReturning = true;

                velocity.x *= -1;
                velocity.y *= -1;


            }
        }
        else {
            float distToEnd = norm(position, endPosition);
            if (distToEnd > 50.0f) {
                APPEARED = false;
            }
        }
    }
}
Itemtype Coin::getItemID() const {
    return Itemtype::COIN;
}
void Coin::Draw() { //animation
    if (Notify == true)
    {
        if (APPEARED) {
            Rectangle sourceRect = {
                frameSize.x * currentFrame,
                0.0f,
                frameSize.x,
                frameSize.y
            };
            Rectangle destRect = { position.x , position.y , size.x * 0.5f, size.y * 0.5f };
            Vector2 origin = { 0, 0 };
            DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
        }
    }
}
Mushroom::Mushroom(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity )
    : Item(startPos, endPos, size, tex, MUSHROOM_FRAME_COUNT, MUSHROOM_FRAME_TIME, velocity, false)
    , isRising(false), riseProgress(0.0f), riseSpeed(1.0f) {}

void Mushroom::applyEffect(Character* character) {
    return;
}
Itemtype Mushroom::getItemID() const {
    return Itemtype::MUSHROOM;
}
void Mushroom::Update(float deltaTime) {
    if (isRising) {
        riseProgress += riseSpeed * deltaTime;
        if(riseProgress >= 1.0f) {
            riseProgress = 1.0f;
            isRising = false;
            APPEARED = true;
        }
    }
    //position.x += velocity.x * deltaTime;
    //position.y += velocity.y * deltaTime;
}
void Mushroom::Accelerate(float deltaTime) {
    velocity.y += gravity * deltaTime;
}
void Mushroom::FlipDirection() {
    velocity.x *= -1;
}
void Mushroom::ResetYVelocity() {
    velocity.y = 0.0f;
}
void Mushroom::startRising() {
    isRising = true;
    riseProgress = 0.0f;
    APPEARED = false;
}

void Mushroom::Draw() {
    if (APPEARED || isRising) {
        Rectangle sourceRect = { 0.0f, 0.0f,
            (float)texture.width, texture.height * riseProgress };
        Rectangle destRect = { position.x, position.y - size.y * riseProgress,
            size.x, size.y * riseProgress };
        Vector2 origin = { 0, 0 };
        DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
    }
}


FireFlower::FireFlower(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity)
    : Item(startPos, endPos, size, tex, FIREFLOWER_FRAME_COUNT, FIREFLOWER_FRAME_TIME, velocity, true) {}
void FireFlower::applyEffect(Character* character) {
    return;
}
Itemtype FireFlower::getItemID() const {
    return Itemtype::FIREFLOWER;
}
void FireFlower::Update(float deltaTime) {
    if (!APPEARED) {
        return;
    }
    elapsedTime += deltaTime;
    if (elapsedTime >= switchTime) {
        currentFrame = (currentFrame + 1) % totalFrames;
        if (currentFrame == 4) {
            currentFrame++;
        }
        elapsedTime = 0.0f;
    }
}
void FireFlower::Draw() {
    if (APPEARED) {
        Rectangle sourceRect = {
            frameSize.x * currentFrame,
            0.0f,
            frameSize.x,
            frameSize.y
        };
        Rectangle destRect = { position.x , position.y , size.x, size.y };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
    }
}
StarMan::StarMan(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 vel) :
    Item(startPos, endPos, size, tex, STARMAN_FRAME_COUNT, STARMAN_FRAME_TIME, vel, true) {}
void StarMan::applyEffect(Character* character) {}
Itemtype StarMan::getItemID() const {
    return Itemtype::STARMAN;
}
void StarMan::Update(float deltaTime) {
    if (!APPEARED) {
        return;
    }
    elapsedTime += deltaTime;
    if (elapsedTime >= switchTime) {
        currentFrame = (currentFrame + 1) % totalFrames;
        if (currentFrame == 4) currentFrame++;
        elapsedTime = 0;
    }
}
void StarMan::Draw() {
    if (APPEARED) {
        Rectangle sourceRect = {
            frameSize.x * currentFrame,
            0.0f,
            frameSize.x,
            frameSize.y
        };
        Rectangle destRect = { position.x , position.y , size.x, size.y };
        Vector2 origin = { 0, 0 };
        DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
    }
}
