#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Character.h"



class Enemy : public Character {
public:
    Enemy(float speed, float jumpHeight);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override = 0;
    virtual void Attack() = 0;

protected:
    float speed;       
    bool isAttacking;  
};


class Goomba : public Enemy {
public:
    Goomba(Vector2 position, float speed);
    ~Goomba();

    void Update(float deltaTime) override;
    void Attack() override;
};


class KoopaTroopa : public Enemy {
public:
    KoopaTroopa(Vector2 position, float speed);
    ~KoopaTroopa();

    void Update(float deltaTime) override;
    void Attack() override;

    void EnterShellMode(); 

private:
    bool isInShellMode;
};


class PiranhaPlant : public Enemy {
public:
    PiranhaPlant(Vector2 position);
    ~PiranhaPlant();

    void Update(float deltaTime) override;
    void Attack() override;
};
#endif