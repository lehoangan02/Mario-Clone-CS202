#pragma once
#include "raylib.h"
#include "../animation/Animation.h"

class Character {
public:
	Character(Texture2D* texture,Vector2 imageCount, float switchTime, float speed, float jumpHeight);
	~Character();
	void Update(float deltaTime);
	void Draw();
	void setPosition(Vector2 position) { this->position = position; };
	Vector2 GetPosition() { return position; };
	Vector2 GetSize() { return size; };
	Vector2 GetCenter();
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
	bool canJump;
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
