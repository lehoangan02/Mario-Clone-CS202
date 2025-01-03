#pragma once
#include "raylib.h"
#include "vector"
#include "string"
#include "../animation/Animation.h"
#include "Fireball.h"
#include "../Sound/Audio.h"

#define MAX_VEC_X = 10.0f
class Command {
public:
	virtual void execute(float deltaTime) = 0;
	virtual ~Command() {};
};

enum slidingDirection {
	right,
	left,
	up,
	down
};

class Character {
public:
	Character(float jumpHeight, float maxSpeed);
	virtual ~Character();
	virtual void Update(float deltaTime)=0;
	void Draw();

	void setPosition(Vector2 position) { this->position = position; };
	void resetVelocity() { velocity.y = 0; };
	void onPlatform() { canJump = true; };

	void setTeleport() { this->teleport = true; };
	void SlidePipe(slidingDirection direction);
	bool isSliding() { return sliding; };
	bool isSlidingFinished() { return finishSliding; };
	void resetSlidingFinished() { finishSliding = false; };
	slidingDirection slideDirection;


	void hitFlag();
	void setPullFlag(bool pullFlag) ;
	bool isPullFlag() { return pullFlag; };

	void touchEnemy();
	void DieAnimation();
	void killEnemy();
	void invincile() { this->isInvincible = true; };
	void powerUp();
	void powerDown();
	void setWin() { isWin = true; };


	void control(bool enabled);
	void accelerate(Vector2 acceleration, float deltaTime);
	void setVelocity(Vector2 velocity) { this->velocity = velocity; };
	float getAcceleration() { return accX; };
	void executeCommand(Command* command, float deltaTime) { command->execute(deltaTime); };


	void increaseScore(int Incre) { this->score += Incre; };
	void increaseScore();;
	int getScore() { return score; }
	void setScore(int score) { this->score = score; }

	int getCoins() { return coins; }
    void setCoins(int coins) { this->coins = coins; }

	bool isflick() { return isflicking; };
	bool isSuper() { return isInvincible; };
	bool haveWon() { return isWin; };
	bool isDead() { return isDie; };
	bool isDeadFinished() { return isFinished; };

	int getType() { return Chartype; };
	int getLives() { return lives; }
	bool getEndGame() { return endGame; }
	bool getPause() { return paused; }
	void increLives();
	void setLives(int lives) { this->lives = lives; }
	
	Vector2 GetPosition() { return position; };
	Vector2 GetSize() { return size; };

	FirePool* firePool;

	void setInvisible() { isVisible = false; };
	void reset();
	void pausePlayer() { paused = true; };
	void continuePlayer() { paused = false; velocity.y = 0; };
protected:
	std::vector<Texture2D> textures;
	std::vector<Vector2> imageCounts;
	int form; //small = 0, big = 1, fire = 2

	Animation animation;
	unsigned int state; //0 = stop , 1 = run

	Vector2 position;
	Vector2 size;
	Vector2 velocity;
	Vector2 SlideDist;

	float jumpHeight;
	float maxSpeed;
	float scale;
	float accX;
	float deadTime;


	bool faceRight;
	bool canJump;
	bool fire;
	bool brake;
	bool teleport;
	bool sliding;
	bool finishSliding;
	bool isDie;
	bool isFinished;
	bool isWin;
	bool endGame;
	bool paused;
	bool pullFlag;

	int Chartype;
	int score;
	int lives;
	int coins;

	void updateFormChangeAnimation();
private:
	bool isChangingForm;
	float formChangeTime;
	float formChangeDuration;
	bool isflicking;
	int flickSwitch;
	float flickDuration;
	bool isVisible;
	int invincibleSwitch;
	float invincibleDuration;
	bool isInvincible;
	Color InvincibleColor;
	void changeForm(int form);
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
	static Character* currentCharacter1;
	static Character* currentCharacter2;
};
class Mario : public Character {
public:
	void Update(float deltaTime) override;
private:
	Mario();
    ~Mario() override {}
	friend class CharacterFactory;
};

class Luigi : public Character {
public:
	void Update(float deltaTime) override;
private:
	Luigi();
    ~Luigi() override {}
	friend class CharacterFactory;

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

class AutoMove : public Command{
private:
	Character* character;
	static float totalTime;
	static float startPosition;

public:
	AutoMove(Character* character) {
		this->character = character;
	}
	void reset() { totalTime = 0.0f; }
	void execute(float deltaTime) override;
};
