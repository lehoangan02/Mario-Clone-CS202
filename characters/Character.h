#pragma once
#include "raylib.h"


class character {
protected:
	Vector2 position ;
	int speed ;
	//not real attribute
	int framesSpeed;
	int frameJump;
	bool onair;
	bool jump;
public:
	character() ;
	virtual ~character() {};
	virtual void render() = 0;
	virtual void controller(int& framesCounter) = 0;
};

enum characterType {
	MARIO,
	LUIGI
};
class characterFactory {
public:
	static character* createCharacter(characterType type);
	static void deleteCharacter();
	static character* getCharacter();

private:
	static character* currentCharacter;
};
