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
    vector<Texture2D> textures;

    Vector2 position;
    Vector2 size;
    Vector2 velocity;

    bool isDown;
    bool isRight;
    bool isDead;
public:
    Enemy() = default;
    void accelerate(float deltaTime);
    virtual void flipDirection();
    virtual void hit();

    Vector2 getPosition() const { return position; };
    void setPosition(Vector2 position) { this->position = position; };

    Vector2 getSize() const { return size; };
    void setSize(Vector2 size) { this->size = size; };
    
    slidingDirection getDirection() const;
    void setDirection(slidingDirection direction);

    bool getIsDead() const { return isDead; };
    virtual EnemyType getEnemyType() const = 0;

    virtual void render();
};

class Goomba : public Enemy {
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