#include "Character.h"
#include <iostream>
using namespace std;
Character::Character(float speed, float jumpHeight) 
{
	this->form = 0;
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->faceRight = true;
	this->state = 0;
	this->velocity = { 0.0f, 0.0f };
	this->canJump = false;
	this->scale = 3.5f;
	this->fire = false;
	this->teleport = true;
	this->sliding = false;
	this->slideDirection = slidingDirection::right;
	position = Vector2{ 20 , 0 };
}

Character::~Character()
{
}
Vector2 Character::GetCenter() {
	return Vector2{ position.x + size.x / 2, position.y + size.y / 2 };
}
void Character::accelerate(Vector2 acceleration, float deltaTime) {
	velocity.x += acceleration.x * deltaTime;
	if (velocity.x > 10.0f)
			velocity.x = 10.0f;
	else if (velocity.x < -10.0f)
		velocity.x = -10.0f;
	velocity.y += acceleration.y * deltaTime;
}
void Character::control(float& accX, bool enabled) {
	if (!enabled) {
		velocity.x = 0;
		return;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		accX = fabs(8.0f);
	}
	else if (IsKeyDown(KEY_LEFT)) {
		accX = -fabs(8.0f);
	}
	else {
		velocity.x = 0.0f;
	}
	if (teleport) {
		if (IsKeyPressed(KEY_D)) {
			sliding = true;
			slideDirection = slidingDirection::right;
		}
		else if (IsKeyPressed(KEY_W)) {
			sliding = true;
			slideDirection = slidingDirection::up;
		}
		else if (IsKeyPressed(KEY_S)) {
			sliding = true;
			slideDirection = slidingDirection::down;
		}
	}
	if (IsKeyPressed(KEY_J)) {
		changeForm(2);
	}
	if (IsKeyPressed(KEY_SPACE) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * 9.81f * jumpHeight);
	}
	if (form==2 && IsKeyPressed(KEY_M)) {
		fire = true;
	}
}
void Character::changeForm(int form) {
	this->form = form;
	size = { (float)textures[form].width / imageCounts[form].x * scale, (float)textures[form].height * scale };
	animation.uvRect = { 0.0f, 0.0f, (float)textures[form].width / imageCounts[form].x, (float)textures[form].height };
}
void Character::Draw()
{
	Rectangle sourceRec = animation.uvRect; // The part of the texture to use for drawing
	Rectangle destRec = { position.x, position.y, fabs(sourceRec.width) * scale, sourceRec.height * scale }; // Destination rectangle with scaling
	float rotation = 0.0f;
	Vector2 origin = { 0.0f, 0.0f };
	DrawTexturePro(textures[form], sourceRec, destRec, origin, rotation, WHITE);
};

Mario::Mario() : Character(500.0f, 5.0f) {
	textures.push_back(LoadTexture("assets/textures/marioSmall.png"));
	textures.push_back(LoadTexture("assets/textures/marioBig.png"));
	textures.push_back(LoadTexture("assets/textures/marioFire.png"));
	imageCounts.push_back({ 6,1 });
	imageCounts.push_back({ 6,1 });
	imageCounts.push_back({ 7,1 });
	float switchTime = 0.1f;
	animation = Animation(&textures[form], imageCounts[form], switchTime);
	size = { (float) textures[form].width / (imageCounts[form].x) * scale, (float)textures[form].height * scale};
	this->SlideDist = { size.x,size.y };
}
void Mario::Update(float deltaTime) {
	if (velocity.y > 0.2f) canJump = false; //handle double jump 
	if (velocity.x == 0.0f || sliding) {
		state = 0;
	}
	else if (!canJump) state = 2;
	else {
		state = 1;
	}
	if (fire) {
		state = 3;
	}
	if (velocity.x >= 0.0f) {
		faceRight = true;
	}
	else {
		faceRight = false;
	}
	animation.Update(state, deltaTime, faceRight, fire);
	setPosition(Vector2{ position.x + velocity.x, position.y + velocity.y });
}

void Character::SlidePipe(slidingDirection direction, float& dist) {
	this->velocity.x = 0;
	this->velocity.y = 0;
	float offset = 0;
	switch (direction) {
	case slidingDirection::right:
		offset = this->size.x /50;
		setPosition({ position.x + offset, position.y });
		this->SlideDist.x -= offset;
		break;
	case slidingDirection::up:
		offset = this->size.y /50;
		setPosition({ position.x , position.y - offset });
		this->SlideDist.y -= offset;
		break;
	case slidingDirection::down:
		offset = this->size.y /50;
		setPosition({ position.x, position.y + offset });
		this->SlideDist.y -= offset;
		break;
	}
	if (this->SlideDist.x <= 0 || this->SlideDist.y <= 0) {
		this->sliding = false;
		this->SlideDist = { this->size.x, this->size.y };
	}
};

Luigi::Luigi() : Character(500.0f, 3.0f) {
	
}
void Luigi::Update(float deltaTime) {

}


Character* CharacterFactory::currentCharacter = nullptr;
void CharacterFactory::deleteCharacter() {
	delete currentCharacter;
	currentCharacter = nullptr;
}
Character* CharacterFactory::createCharacter(CharacterType type) {
	deleteCharacter();
	switch (type) {
	case MARIO:
		currentCharacter = new Mario();
		break;
	case LUIGI:
		currentCharacter = new Luigi();
		break;
	default:
		currentCharacter = nullptr;
	}
	return currentCharacter;

}

void FullControl::execute(float deltaTime) {
	if (character->sliding) {
		float dist = 10.0f;
		character->SlidePipe(character->slideDirection, dist);
		character->Update(deltaTime);
	}
	else {
		float accX = 0;
		character->control(accX, true);
		character->accelerate(Vector2{ accX, 9.81f }, deltaTime);

		character->Update(deltaTime);
	}
}
void InHole::execute(float deltaTime) {
	float accX = 0;
	character->control(accX, false);
	character->accelerate(Vector2{ accX, 9.81f }, deltaTime);
	character->Update(deltaTime);
}
void SlidePipeRight::execute(float deltaTime) {
	/*float accX = 0;
	character->control(accX, false);
	slideTime -= deltaTime;
	if (slideTime > 0) {
		character->setPosition(Vector2{ character->GetPosition().x + 5, character->GetPosition().y });
	}
	else character->sliding = false;
	character->Update(deltaTime);*/
}
void SlidePipeUp::execute(float deltaTime) {
	float accX = 0;
	character->control(accX, false);
	slideTime -= deltaTime;
	if (slideTime < 0) {
		character->executeCommand(new FullControl(character), deltaTime);
	}
	character->setPosition(Vector2{ character->GetPosition().x, character->GetPosition().y - 5 });
	character->Update(deltaTime);
}
void SlidePipeDown::execute(float deltaTime) {
	float accX = 0;
	character->control(accX, false);
	slideTime -= deltaTime;
	if (slideTime < 0) {
		character->executeCommand(new FullControl(character), deltaTime);
	}
	character->setPosition(Vector2{ character->GetPosition().x, character->GetPosition().y + 5 });
	character->Update(deltaTime);
}

