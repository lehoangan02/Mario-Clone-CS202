#include "Item.h"
#include <iostream>
#include <math.h>
Item::Item(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, int totalFrames, float switchTime, Vector2 velocity)
    : startPosition(startPos), endPosition(endPos), size(size), texture(tex),
    totalFrames(totalFrames), switchTime(switchTime), velocity(velocity),
     elapsedTime(0), currentFrame(0), APPEARED(true)
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
void Item::Update(float deltaTime) {
    if (!APPEARED) {
        return;
    }

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    if (fabs(position.x - endPosition.x) <= fabs(velocity.x * deltaTime) &&
        fabs(position.y - endPosition.y) <= fabs(velocity.y * deltaTime)) {
        velocity.x = -velocity.x;
        velocity.y = -velocity.y;
        moves++;
    }

    if (fabs(position.x - startPosition.x) <= fabs(velocity.x * deltaTime) &&
        fabs(position.y - startPosition.y) <= fabs(velocity.y * deltaTime)) {
        if (moves >= 1) {
            APPEARED = false; 
        }
    }
    
    
}
void Item::Draw() {
    if (APPEARED) {
        Rectangle destRect = { position.x, position.y, size.x, size.y }; 
        Rectangle sourceRect = { 0.0f, 0.0f, (float)texture.width, (float)texture.height }; 
        Vector2 origin = { 0, 0 }; 
        DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE); 
    }
}
Coin::Coin(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity)
    : Item(startPos, endPos, size, tex, COIN_FRAME_COUNT, COIN_FRAME_TIME, velocity) {}
void Coin::applyEffect(Character* character) {
    return;
}
Mushroom::Mushroom(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity)
    : Item(startPos, endPos, size, tex, MUSHROOM_FRAME_COUNT, MUSHROOM_FRAME_TIME, velocity) {}

void Mushroom::applyEffect(Character* character) {
    return;
}
FireFlower::FireFlower(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity)
    : Item(startPos, endPos, size, tex, FIREFLOWER_FRAME_COUNT, FIREFLOWER_FRAME_TIME, velocity) {}
void FireFlower::applyEffect(Character* character) {
    return;
}
