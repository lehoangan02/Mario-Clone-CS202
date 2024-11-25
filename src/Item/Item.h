#pragma 

constexpr int COIN_FRAME_COUNT = 4;
constexpr float COIN_FRAME_TIME = 0.1f;

constexpr int MUSHROOM_FRAME_COUNT = 6;
constexpr float MUSHROOM_FRAME_TIME = 0.08f;

constexpr int FIREFLOWER_FRAME_COUNT = 5;
constexpr float FIREFLOWER_FRAME_TIME = 0.12f;

#include "../animation/Animation.h"
#include "../characters/Character.h"



class Item {
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
	Vector2 velocity;
public:
	Item(Vector2 pos, Vector2 size, Texture2D texture, int totalFrames, float switchTime, Vector2 velocity);
	virtual ~Item();
	virtual void applyEffect(Character* character) = 0;
	virtual void Update(float deltaTime);
	virtual void Draw();

	Vector2 GetPosition() const {
		return position;
	}
	Vector2 GetSize() const {
		return size;
	}

};
class Coin : public Item {
public:
	Coin(Vector2 pos, Vector2 size, Texture2D tex, Vector2 velocity);
	void applyEffect(Character* Character) override;

};
class Mushroom : public Item {
public:
	Mushroom(Vector2 pos, Vector2 size, Texture2D tex, Vector2 velocity);
	void applyEffect(Character* character);

};
class FireFlower : public Item {
public:
	FireFlower(Vector2 pos, Vector2 size, Texture2D tex, Vector2 velocity);
	void applyEffect(Character* character);
};


