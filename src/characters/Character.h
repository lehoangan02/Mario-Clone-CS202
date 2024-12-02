#pragma once
#include "raylib.h"
#include "vector"
#include "../animation/Animation.h"

class Character {
public:
	Character(float speed, float jumpHeight);
	~Character();
	virtual void Update(float deltaTime)=0;
	void Draw();
	void setPosition(Vector2 position) { this->position = position; };
	Vector2 GetPosition() { return position; };
	Vector2 GetSize() { return size; };
	Vector2 GetCenter();

	void autoMove(float deltaTime);
	void control(float& accX, bool enabled);
	void accelerate(Vector2 acceleration, float deltaTime);
	void onPlatform() { canJump = true; }; // lehoangan added, if there are any issues, please contact me
	void resetVelocity() { velocity = { 0,0 }; }; // lehoangan added, if there are any issues, please contact me
protected:
	std::vector<Texture2D> textures;
	std::vector<Vector2> imageCounts;
	int form; //small = 0, big = 1, fire = 2
	Animation animation;

	Vector2 position;
	Vector2 size;
	Vector2 velocity;

	unsigned int state; //0 = stop , 1 = run

	float speed;
	float jumpHeight;

	bool faceRight;
	bool canJump = true;
	bool fire;

	float scale ;
};

//CharacterFactory
enum CharacterType {
	MARIO,
	LUIGI
};
class CharacterFactory {
public:
	static Character* createCharacter(CharacterType type);
	static void deleteCharacter();

private:
	static Character* currentCharacter;
};
class Mario : public Character {
public:
	Mario() ;
	void Update(float deltaTime) override;

};

class Luigi : public Character {
public:
	Luigi();
	void Update(float deltaTime) override;

};