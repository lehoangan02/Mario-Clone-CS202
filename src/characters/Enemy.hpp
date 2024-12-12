#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Character.h"
#include <vector>

enum class EnemyType {
	GOOMBA,
    KOOPA_TROOPA,
    PIRANHA_PLANT,
    LAKITU,
    SHY_GUY
};

class Enemy{
protected:
    Texture2D texture;
    std::vector<Texture2D> textures;

    Vector2 originPosition;
    Vector2 position;
    Vector2 size;
    Vector2 speed;

    bool isDown;
    bool isRight;
    bool isDead;

    float animationTime;       
    float timer;               
    int currentTextureIndex;   
public:
    Enemy() = default;
    Enemy(Vector2 position) : position(position), animationTime(1.0f), timer(0.0f), currentTextureIndex(0) {}

    void accelerate(float deltaTime);
    virtual void flipDirection();
    virtual void hit();
    void resetSpeedY() { speed.y = 0; isDown = false; }

    Vector2 getPosition() const { return position; };
    void setPosition(Vector2 position) { this->position = position; };

    Vector2 getSize() const { return size; };
    void setSize(Vector2 size) { this->size = size; };
    
    slidingDirection getDirection() const;
    void setDirection(slidingDirection direction);

    bool getIsDead() const { return isDead; };
    virtual EnemyType getEnemyType() const = 0;

    virtual void update(float deltaTime) = 0;

    virtual void render();
};

class Goomba : public Enemy {
private:
    bool isCollisionTrue;
    bool isDying;
    float dyingTime;
public:
    Goomba(Vector2 position);
    EnemyType getEnemyType() const override { return EnemyType::GOOMBA; };

    bool setCollisionTrue(bool isCollisionTrue) { this->isCollisionTrue = isCollisionTrue; };
    void hit() override;
    void update(float deltaTime) override;
    void render() override;
};

class KoopaTroopa : public Enemy {
};

class PiranhaPlant : public Enemy {
};

class Lakitu : public Enemy {
};

class ShyGuy : public Enemy {
};
#endif // !ENEMY_HPP