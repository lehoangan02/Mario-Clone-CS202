#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Character.h"
#include <vector>

enum class EnemyType {
	GOOMBA,
    KOOPA_TROOPA,
    PIRANHA_PLANT,
    INVERSE_PIRANHA_PLANT,
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
    bool isCollisionTrue;

    float animationTime;       
    float timer;               
    int currentTextureIndex;

    float leftBound, rightBound, topBound, bottomBound;   
public:
    Enemy() = default;
    Enemy(Vector2 position) : position(position), animationTime(1.0f), timer(0.0f), currentTextureIndex(0) {}
    Enemy(Vector2 position, Vector2 size, Vector2 speed) : position(position), size(size), speed(speed), animationTime(1.0f), timer(0.0f), currentTextureIndex(0) {}
    Enemy(Vector2 position, Vector2 size, Vector2 speed, float leftBound, float rightBound, float topBound, float bottomBound) : position(position), size(size), speed(speed), leftBound(leftBound), rightBound(rightBound), topBound(topBound), bottomBound(bottomBound), animationTime(1.0f), timer(0.0f), currentTextureIndex(0) {}

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

    void setDead(bool isDead) { this->isDead = isDead; };
    bool getIsDead() const { return isDead; };
    bool setCollisionTrue(bool isCollisionTrue) { this->isCollisionTrue = isCollisionTrue; };
    virtual EnemyType getEnemyType() const = 0;

    void setBound(float left, float right, float top, float bottom) ;
    virtual Rectangle getBoundingBox() const = 0;

    virtual void update(float deltaTime) = 0;

    virtual void render();
};
//isCollisionTrue la neu va cham true thi se chuyen sang texture flat vai khung hinh roi chet, other is die...
class Goomba : public Enemy {
private:
    bool isDying;
    float dyingTime;
public:
    Goomba(Vector2 position);
    Goomba(Vector2 position, Vector2 size, Vector2 speed);
    EnemyType getEnemyType() const override { return EnemyType::GOOMBA; };

    Rectangle getBoundingBox() const { return {position.x, position.y, size.x, size.y}; };
    void hit() override;
    void update(float deltaTime) override;
    void render() override;
};

class KoopaTroopa : public Enemy {
    private:
        bool isShell;
        Vector2 shellSpeed;
    public:
        KoopaTroopa(Vector2 position);
        KoopaTroopa(Vector2 position, Vector2 size, Vector2 speed);
        KoopaTroopa(Vector2 position, Vector2 size, Vector2 speed, float leftBound, float rightBound, float topBound, float bottomBound);
        EnemyType getEnemyType() const override { return EnemyType::KOOPA_TROOPA; };

        void setShell(bool isShell) { this->isShell = isShell; };
        bool getIsShell() const { return isShell; };
        
        void setShellSpeed( Vector2 shellSpeed) { this->shellSpeed = shellSpeed; };
        Vector2 getShellSpeed() const { return shellSpeed; };

        Rectangle getBoundingBox() const { return {position.x, position.y, size.x, size.y}; };
        void hit() override;
        void update(float deltaTime) override;
        void render() override;
};

class PiranhaPlant : public Enemy {
    protected:
        float heightInGround;
        bool isPauseCollision;
    public:
        PiranhaPlant(Vector2 position);
        PiranhaPlant(Vector2 position, Vector2 size, Vector2 speed);
        EnemyType getEnemyType() const override { return EnemyType::PIRANHA_PLANT; };

        void setHeightInGround(float heightInGround) { this->heightInGround = heightInGround; };
        float getHeightInGround() const { return heightInGround; };
        void setIsPauseCollision(bool isPauseCollision) { this->isPauseCollision = isPauseCollision; };
        virtual Rectangle getBoundingBox () const { return {position.x, position.y, size.x, size.y - heightInGround}; };

        void hit() override;
        virtual void update(float deltaTime) override;
        virtual void render() override;
};
//size of piranha plant should be scale of 32x66
//position is the top left of piranha full out of ground.

// chieu cao noi tren ong = size.y - heightInGround
//dung isPauseCollision thi no se cho pause vai khung hinh cua piranha sau va cham

//position of inverse piranha plant is the left of ground
class InversePiranhaPlant : public PiranhaPlant {
    public:
        InversePiranhaPlant(Vector2 position);
        InversePiranhaPlant(Vector2 position, Vector2 size, Vector2 speed);

        Rectangle getBoundingBox() const override { return {originPosition.x, originPosition.y, size.x, size.y - heightInGround}; };
        void update(float deltaTime) override;
        void render() override;
        void test();
};
class Lakitu : public Enemy {
};

//size of shy guy should be scale of 21x29
//neu va cham dung thi shy guy moi bien mat(tuc ham hit duoc goi se set isDead = true neu isCollisionTrue = true)
class ShyGuy : public Enemy {
    public:
        ShyGuy(Vector2 position);
        ShyGuy(Vector2 position, Vector2 size, Vector2 speed);
        ShyGuy(Vector2 position, Vector2 size, Vector2 speed, float leftBound, float rightBound, float topBound, float bottomBound);
        EnemyType getEnemyType() const override { return EnemyType::SHY_GUY; };

        Rectangle getBoundingBox() const { return {position.x, position.y, size.x, size.y}; };
        void hit() override;
        void update(float deltaTime) override;
        void render() override;

};
#endif // !ENEMY_HPP