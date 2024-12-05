#pragma once
#include "raylib.h"
#include "../animation/Animation.h"

class Character {
public:
    Character() = default;
	Character(Texture2D* texture,Vector2 imageCount, float switchTime, float speed, float jumpHeight);
	~Character();
	void Update(float deltaTime);
	void Draw();
	void setPosition(Vector2 position) { this->position = position; };
	Vector2 GetPosition() { return position; };
	Vector2 GetSize() { return size; };
	Vector2 GetCenter();

	void control(float& accX, bool enabled);
	void accelerate(Vector2 acceleration, float deltaTime);
	void onPlatform() { canJump = true; }; // lehoangan added, if there are any issues, please contact me
	void resetVelocity() { velocity = { 0,0 }; }; // lehoangan added, if there are any issues, please contact me
protected:
	Texture2D texture;
	Animation animation;

	Vector2 position;
	Vector2 size;
	Vector2 velocity;

	unsigned int state; //0 = stop , 1 = run

	float speed;
	float jumpHeight;

	bool faceRight;
	bool canJump = true;
};

//enum CharacterType {
//	MARIO,
//	LUIGI
//};
//class CharacterFactory {
//public:
//	static Character* createCharacter(CharacterType type);
//	static void deleteCharacter();
//	static Character* getCharacter();
//
//private:
//	static Character* currentCharacter;
//};
