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
private:
	bool isChangingForm;
	float formChangeTime;
	float formChangeDuration;
	bool isflicking;
	int flickSwitch;
	float flickDuration;
	bool isVisible;
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
	void updateFormChangeAnimation();
	void executeCommand(Command* command, float deltaTime) { command->execute(deltaTime); };

	void setTeleport() { this->teleport = true; };
	void SlidePipe(slidingDirection direction);
	bool isSliding() { return sliding; };

	void setVelocity(Vector2 velocity) { this->velocity = velocity; };

	void hitFlag(Vector2 flagPos);

	void setScore(int newscore) { this->score = newscore; };
	int getScore() { return score; }

	bool haveWon() { return isWin; };
	void setWin() { isWin = true; };

	void powerUp();
	void powerDown(); //need invicile effect

	void touchEnemy();
	bool isDead() { return isDie; };
	bool isflick() { return isflicking; };
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
	bool isDie;

	float scale ;

	Vector2 SlideDist;
	bool teleport;

	bool pullFlag;

	int score;

	bool isWin;
	void changeForm(int form);

public:
	float accX;
	bool sliding;
	slidingDirection slideDirection;
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

class AutoMove : public Command {
private:
	Character* character;
	float totalTime; 
	static AutoMove* instance; 
	AutoMove(Character* character) : totalTime(0.0f) { this->character = character; }

public:
	static AutoMove* getInstance(Character* character) {
		if (instance == nullptr) {
			instance = new AutoMove(character);
		}
		return instance;
	}
	void reset() {totalTime = 0.0f;}
	void execute(float deltaTime) override;
};
