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

enum class Itemtype {
	COIN,
	MUSHROOM,
	FIREFLOWER,
	STARMAN
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
	
	Vector2 velocity;
	Vector2	startPosition;
	Vector2 endPosition;
	bool APPEARED;
	bool isReturning;
	int moves;

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
	static Item* Transform(Item* currentItem, const std::string& newItemType,
		Texture2D newTexture, int newTotalFrames, float newSwitchTime);
};
class Coin : public Item {
public:
	void onNotify() override;
	Coin(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity);
	void applyEffect(Character* Character) override;
	void Update(float deltaTime) override;
	void Draw() override;
	Itemtype getItemID() const override;

};
class Mushroom : public Item {
private:
	bool isFalling;
	float gravity = 1000;
	bool isRising;
	float riseProgress;
	float riseSpeed;
	bool FinishedSpawning;
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

};
class FireFlower : public Item {
private:
	bool isRising;
	float riseProgress;
	float riseSpeed;
	bool FinishedSpawning;
	
public:
	FireFlower(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity = {0, 0});
	void applyEffect(Character* character);
	void onNotify() override;
	void Update(float deltaTime) override;
	void Draw() override;
	Itemtype getItemID() const override;
	bool isFinishedSpawning() { return FinishedSpawning; }
};
class StarMan : public Item {
private:
	bool isRising;
	float riseProgress;
	float riseSpeed;
	bool FinishedSpawning;
public:
	StarMan(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity = {0, 0});
	void onNotify() override;
	void applyEffect(Character* character);
	void Update(float deltaTime) override;
	void Draw() override;
	Itemtype getItemID() const override;
	bool isFinishedSpawning() { return FinishedSpawning; }

};

