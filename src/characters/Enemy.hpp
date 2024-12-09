#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Character.h"

class Enemy : public Character {
public:
    Enemy();
    virtual ~Enemy();
};

class Goomba : public Enemy {
public:
    Goomba();
    ~Goomba();
};

class KoopaParatroopa : public Enemy {
public:
    KoopaParatroopa();
    ~KoopaParatroopa();
};

class Lakitu : public Enemy {
public:
    Lakitu();
    ~Lakitu();
};

class PiranhaPlant : public Enemy {
public:
    PiranhaPlant();
    ~PiranhaPlant();
}
#endif