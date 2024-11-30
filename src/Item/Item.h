#pragma 
constexpr float epsilon = 1.0f;

constexpr int COIN_FRAME_COUNT = 6;
constexpr float COIN_FRAME_TIME = 0.05f;

constexpr int MUSHROOM_FRAME_COUNT = 6;
constexpr float MUSHROOM_FRAME_TIME = 0.5f;

constexpr int FIREFLOWER_FRAME_COUNT = 5;
constexpr float FIREFLOWER_FRAME_TIME = 0.12f;

#include "../animation/Animation.h"
#include "../characters/Character.h"
#include "../Oberver/Observer.hpp"

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
	virtual void onNotify() override;
	Item(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D texture, int totalFrames, float switchTime, Vector2 velocity);
	virtual ~Item();
	virtual void applyEffect(Character* character) = 0;
	virtual void Update1(float deltaTime); //acceleration
	virtual void Update(float deltaTime); // not acceleration
	virtual void Draw(); // not animation
	virtual void Draw1(); // animation
	float norm(Vector2 vector1, Vector2 vector2);
	Vector2 GetPosition() const {
		return position;
	}
	Vector2 GetSize() const {
		return size;
	}

};
class Coin : public Item {
public:
	Coin(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity);
	void applyEffect(Character* Character) override;

};
class Mushroom : public Item {
public:
	Mushroom(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity);
	void applyEffect(Character* character);

};
class FireFlower : public Item {
public:
	FireFlower(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity);
	void applyEffect(Character* character);
};

