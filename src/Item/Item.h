#pragma 
constexpr float epsilon = 1.0f;

constexpr int COIN_FRAME_COUNT = 6;
constexpr float COIN_FRAME_TIME = 0.05f;

constexpr int MUSHROOM_FRAME_COUNT = 6;
constexpr float MUSHROOM_FRAME_TIME = 0.5f;

constexpr int FIREFLOWER_FRAME_COUNT = 4;
constexpr float FIREFLOWER_FRAME_TIME = 0.05f;

constexpr int STARMAN_FRAME_COUNT = 4;
constexpr float STARMAN_FRAME_TIME = 0.05f;

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
	virtual void Update(float deltaTime); 
	virtual void Draw(); // not animation
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
	void Update(float deltaTime) override;
	void Draw() override;

};
class Mushroom : public Item {
public:
	Mushroom(Vector2 startPos, Vector2 endPos , Vector2 size, Texture2D tex, Vector2 velocity = {0, 0});
	void applyEffect(Character* character);
	void Update(float deltaTime) override;
	void Draw() override;

};
class FireFlower : public Item {
public:
	FireFlower(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity = {0, 0});
	void applyEffect(Character* character);
	void Update(float deltaTime) override;
	void Draw() override;
};
class StarMan : public Item {
public:
	StarMan(Vector2 startPos, Vector2 endPos, Vector2 size, Texture2D tex, Vector2 velocity = {0, 0});
	void applyEffect(Character* character);
	void Update(float deltaTime) override;
	void Draw() override;


};

