#pragma once
#include "raylib.h"
#include "vector"
#include "string"
#include "../animation/Animation.h"

#define MAX_VEC_X = 10.0f
class Command {
public:
	virtual void execute(float deltaTime) = 0;
	virtual ~Command() {};
};

enum slidingDirection {
	right,
	up,
	down
};

class Character {
public:

	Character(float jumpHeight);
	~Character();
	virtual void Update(float deltaTime)=0;
	void Draw();
	void setPosition(Vector2 position) { this->position = position; };
	Vector2 GetPosition() { return position; };
	Vector2 GetSize() { return size; };
	Vector2 GetCenter();

	void control(bool enabled);
	void accelerate(Vector2 acceleration, float deltaTime);
	void onPlatform() { canJump = true; }; // lehoangan added, if there are any issues, please contact me
	void resetVelocity() { velocity.y = 0; }; // lehoangan added, if there are any issues, please contact me
	void changeForm(int form);
	void executeCommand(Command* command, float deltaTime) { command->execute(deltaTime); };
	void SlidePipe(slidingDirection direction);
protected:
	std::vector<Texture2D> textures;
	std::vector<Vector2> imageCounts;
	int form; //small = 0, big = 1, fire = 2
	Animation animation;

	Vector2 position;
	Vector2 size;
	Vector2 velocity;

	unsigned int state; //0 = stop , 1 = run

	float jumpHeight;

	bool faceRight;
	bool canJump;
	bool fire;
	bool brake;

	float scale ;

	Vector2 SlideDist;
	bool teleport;

public:
	float accX;
	bool sliding;
	slidingDirection slideDirection;

	int points;
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

class FullControl : public Command {
private:
	Character* character;
public:
	FullControl(Character* Player) { this->character = Player; };
	void execute(float deltaTime) override;
};
class InHole : public Command {
private:
	Character* character;
public:
	InHole(Character* Player) { this->character = Player; };
	void execute(float deltaTime) override;
};

