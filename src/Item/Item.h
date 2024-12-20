#pragma once

constexpr float epsilon = 1.0f;

constexpr int COIN_FRAME_COUNT = 6;
constexpr float COIN_FRAME_TIME = 0.05f;

constexpr int MUSHROOM_FRAME_COUNT = 6;
constexpr float MUSHROOM_FRAME_TIME = 0.2f;

constexpr int FIREFLOWER_FRAME_COUNT = 5;
constexpr float FIREFLOWER_FRAME_TIME = 0.5f;

constexpr int STARMAN_FRAME_COUNT = 5;
constexpr float STARMAN_FRAME_TIME = 0.5f;

#include <string>
#include "raylib.h"
#include "../characters/Character.h"
#include "../Oberver/Observer.hpp"

enum Itemtype {
	COIN,
	MUSHROOM,
	FIREFLOWER,
	STARMAN,
	IDLECOIN
};

class Item : public Observer {
protected:
	Vector2 position;
	Vector2 size;
	Texture2D texture;
	Rectangle uvRect;  // Khu vuc texture hien thi
	Vector2 frameSize;
	int totalFrames;
	int currentFrame;
	float switchTime;  // Thoi gian chuyen doi giua cac frame
	float elapsedTime; // Thoi gian troi qua tu lan doi frame truoc
	bool Notify;
	bool hit;
	Vector2 velocity;
	Vector2	startPosition;
	Vector2 endPosition;
	bool APPEARED;
	bool isReturning;
	int moves;
	bool FinishedSpawning;
public:
	Item(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D texture, int totalFrames, float switchTime, Vector2 velocity, bool appeared);
	virtual ~Item();
	void onNotify() override {}
	virtual void applyEffect(Character* character) = 0;
	virtual void Update(float deltaTime); 
	virtual void Draw(); // not animation
	float norm(Vector2 vector1, Vector2 vector2);
	virtual Itemtype getItemID() const = 0;
	Vector2 GetPosition() const {
		return position;
	}
	Vector2 GetSize() const {
		return size;
	}
	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}
	virtual void setHit() = 0;
	virtual bool isHit() = 0;
	static Item* Transform(Item* currentItem, const std::string& newItemType,
		Texture2D newTexture, int newTotalFrames, float newSwitchTime);
};
class IdleCoin {
private:
	Vector2 position;
	Vector2 size;
	Texture2D texture;
	Rectangle uvRect;
	Vector2 frameSize;
	int totalFrames;
	int currentFrame;
	float switchTime;
	float elapsedTime;
	bool APPEARED;
	bool hit;
public:
	IdleCoin(Vector2 startPos, Vector2 size, Texture2D texture);
	Itemtype getItemID() const;
	void Update(float deltaTime);
	void Draw();
	bool isHit();
	void stopDrawing();
	Vector2 getPosition() const;
	Vector2 getSize() const;
	void setHit();
	~IdleCoin();
};
class Coin : public Item {
private:
public:
	void onNotify() override;
	Coin(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity = { 0,0 });
	void applyEffect(Character* Character) override;
	void Update(float deltaTime) override;
	void Draw() override;
	Itemtype getItemID() const override;
	bool isHit() override { return hit; }
	void setHit() override {
		hit = true;
		APPEARED = false;
	}

};
class Mushroom : public Item {
private:
	bool isFalling;
	float gravity = 100;
	bool isRising;
	float riseProgress;
	float riseSpeed;
public:
	Mushroom(Vector2 startPos, Vector2 endPos , Vector2 size, Texture2D tex, Vector2 velocity);
	void onNotify() override;
	void applyEffect(Character* character);
	void Accelerate(float deltatime);
	void FlipDirection();
	void ResetYVelocity();
	void Update(float deltaTime) override;
	void Draw() override;
	void Rising(float deltaTime);
	Itemtype getItemID() const override;
	bool isFinishSpawning() { return FinishedSpawning; }
	bool isHit() override;
	void setHit() override;

};
class FireFlower : public Item {
private:
	bool isRising;
	float riseProgress;
	float riseSpeed;
	
public:
	FireFlower(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity = {0, 0});
	void applyEffect(Character* character);
	void onNotify() override;
	void Update(float deltaTime) override;
	void Draw() override;
	Itemtype getItemID() const override;
	bool isFinishedSpawning() { return FinishedSpawning; }
	void setHit() override {
		hit = true;
		APPEARED = false;
	}
	bool isHit() override { return hit; }
};
class StarMan : public Item {
private:
	bool isRising;
	float gravity = 2.0;
	float riseProgress;
	float riseSpeed;
	bool onFalling;
	
public:
	StarMan(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity = {0, 0});
	void onNotify() override;
	void applyEffect(Character* character);
	void Update(float deltaTime) override;
	void Draw() override;
	Itemtype getItemID() const override;
	bool isFinishedSpawning() { return FinishedSpawning; }
	void Move(float upperBoundary, float lowerBoundary, float deltaTime);
	void setHit() override {
		hit = true;
		APPEARED = false;
	}
	bool isHit() override {
		return hit;
	}

	void slantDirection();
	void Accelerate(float deltaTime);
	void FlipDirection();
	void setFalling();
	void FlipDirectionX();
	void FlipDirectionY();
};

