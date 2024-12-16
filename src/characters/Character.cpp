#include "Character.h"
#include <iostream>

#define MAX_SPEED 700.0f
#define FAST_BRAKE 1400.0f
#define ACC_X 600.0f
#define SLOW_BRAKE 800.0f
#define GRAVITY 3500.0f

Character::Character(float jumpHeight) 
{
	this->form = 0;
	this->accX = 0.0f;
	this->jumpHeight = jumpHeight;
	this->faceRight = true;
	this->state = 0;
	this->velocity = { 0.0f, 0.0f };
	this->accX = 0.0f;
	this->canJump = false;
	this->scale = 5.0f;
	this->fire = false;
	this->teleport = true;
	this->sliding = false;
	this->brake = false;
	this->slideDirection = slidingDirection::right;
	this->isChangingForm = false;
	this->pullFlag = false;
	this->isWin = false;
	this->isDie = false;
	this->isflicking = false;
	this->flickSwitch = 0;
	this->flickDuration = 3.0f;
	this->isVisible = true;
	this->invincibleDuration = 6.0f;
	this->invincibleSwitch = 0;
	this->isInvincible = false;
	this->InvincibleColor = WHITE;
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
	if (velocity.x > MAX_SPEED)
			velocity.x = MAX_SPEED;
	else if (velocity.x < -MAX_SPEED) 
		velocity.x = -MAX_SPEED;
	velocity.y += acceleration.y * deltaTime;
	/*std::cout << "velocity: " << velocity.x << " " << velocity.y << std::endl;*/
}
void Character::control(bool enabled) {
	if (!enabled) {
		/*velocity.x = 0;*/
		return;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		if (velocity.x < - MAX_SPEED * 3 / 5) brake = true;
		if (brake) accX = fabs(FAST_BRAKE);
		else accX = fabs(ACC_X);
	}
	else if (IsKeyDown(KEY_LEFT)) {
		if (velocity.x > MAX_SPEED * 3 / 5) brake = true;
		if (brake) accX = -fabs(FAST_BRAKE);
		else accX = -fabs(ACC_X);
	}
	else {
		if (faceRight) accX = -fabs(SLOW_BRAKE);
		else accX = fabs(SLOW_BRAKE);
		if (fabs(velocity.x) < MAX_SPEED*1/10) {
			velocity.x = 0.0f;
			accX = 0;
		}
	}
	if (teleport) {
		if (IsKeyPressed(KEY_S)) {
			sliding = true;
			slideDirection = slidingDirection::down;
		}
	}
	if (IsKeyPressed(KEY_J)) {
		powerUp();
	}
	if (IsKeyPressed(KEY_K)) {
		powerDown();
	}
	if (IsKeyPressed(KEY_H)) {
		touchEnemy();
	}
	if (IsKeyPressed(KEY_I)) {
		invincile();
	}
	if (IsKeyPressed(KEY_Q)) {
		pullFlag = true;
	}
	if (IsKeyPressed(KEY_SPACE) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
	}
	if (form==2 && IsKeyPressed(KEY_M)) {
		fire = true;
	}
}
void Character::changeForm(int form) {
	this->form = form;
	size = { (float)textures[form].width / imageCounts[form].x * scale, (float)textures[form].height * scale };
	animation.uvRect = { 0.0f, 0.0f, (float)textures[form].width / imageCounts[form].x, (float)textures[form].height };
	isChangingForm = true;
	formChangeTime = 0.0f;
	formChangeDuration = 24.0f; // Duration of the form change animation in seconds
}
void Character::updateFormChangeAnimation() {
	if (isChangingForm) {
		velocity.y = 0;
		velocity.x = 0;
		if ((int) formChangeTime % 8 == 0) {
			scale = 2.0f + formChangeTime * 0.125f;
		}
		else if ((int) formChangeTime % 4 ==0)  scale = scale - 0.2f;
		formChangeTime += 1.0f;
		if (formChangeTime > formChangeDuration) {
			isChangingForm = false;
		}
	}
	if (isflicking) {
		flickSwitch += 1;
		if (flickSwitch % 3 ==0) isVisible = !isVisible;

		flickDuration -= GetFrameTime();
		if (flickDuration <0.0f) {
			isflicking = false;
			isVisible = true;
			flickDuration = 3.0f;
		}
	}
	if (isInvincible) {
		invincibleSwitch += 1;
		if (invincibleSwitch % 21 == 0) InvincibleColor = Color { 0, 228, 48, 200 };
		else if (invincibleSwitch % 21 == 7) InvincibleColor = Color{ 190, 33, 55, 200 };
		else if (invincibleSwitch % 21 == 14) InvincibleColor = Color{ 255,255,255,200 };

		invincibleDuration -= GetFrameTime();
		if (invincibleDuration < 0.0f) {
			isInvincible = false;
			InvincibleColor = WHITE;
			invincibleDuration = 6.0f;
		}
	}
	/*std::cout << "Size: " << size.x << " " << size.y << std::endl;
	std::cout << "scale: " << scale << std::endl;*/
}
void Character::hitFlag(Vector2 flagPos) {
	/*if (!pullFlag) {
		std::cout << "not pull flag" << std::endl;
		return;
	};
	static const float Speed =100;
	static const float EndPosition = 600;
	position.x = flagPos.x;
	position.y += Speed*
	if (position.y > EndPosition)
	{
		std::cout << "Cc";
		position.y = 1;
		pullFlag = false;
	}*/
}

void Character::powerUp() {
	if (form == 0) {
		changeForm(1);
	}
	else if (form == 1) {
		changeForm(2);
	}
}
void Character::powerDown() {
	isflicking = true;
	flickSwitch = 0;
	changeForm(0);
}

void Character::touchEnemy() {
    if (form != 0) {
		powerDown();
		return;
	}
	else {
		velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
		isDie = true;
	}
}
void Character::Draw()
{
	if (!isVisible) return;
	//std::cout << "velocity: " << velocity.x << " " << velocity.y << std::endl;
	Rectangle sourceRec = animation.uvRect; // The part of the texture to use for drawing
	Rectangle destRec = { position.x, position.y, fabs(sourceRec.width) * scale, sourceRec.height * scale }; // Destination rectangle with scaling
	float rotation = 0.0f;
	Vector2 origin = { 0.0f,0.0f };
	DrawTexturePro(textures[form], sourceRec, destRec, origin, rotation, InvincibleColor);
};

Mario::Mario() : Character(300.0f) {
	textures.push_back(LoadTexture("assets/textures/marioSmall2.png"));
	textures.push_back(LoadTexture("assets/textures/marioBig2.png"));
	textures.push_back(LoadTexture("assets/textures/marioFire2.png"));
	imageCounts.push_back({ 7,1 });
	imageCounts.push_back({ 6,1 });
	imageCounts.push_back({ 7,1 });
	float switchTime = 0.1f;
	animation = Animation(&textures[form], imageCounts[form], switchTime);
	size = { (float) textures[form].width / (imageCounts[form].x) * scale, (float)textures[form].height * scale};
	this->SlideDist = { size.x,size.y };
}
void Mario::Update(float deltaTime) {
	if (velocity.y > GRAVITY*deltaTime*1.2f) canJump = false; //handle double jump 
	if (velocity.x == 0.0f || sliding) {
		state = 0;
	}
	else if (!canJump) state = 2;
	else if (brake) state = 4;
	else {
		state = 1;
	}
	if (fire) {
		state = 3;
	}
	if (velocity.x > 0.0f) {
		faceRight = true;
	}
	else if (velocity.x < 0.0f) {
		faceRight = false;
	}

	if (isDie) {
		velocity.x = 0;
		state = 5;
	}
	animation.Update(state, deltaTime, faceRight, fire, brake);
	updateFormChangeAnimation();
	setPosition(Vector2{ position.x + velocity.x*deltaTime, position.y + velocity.y * deltaTime });
}

void Character::SlidePipe(slidingDirection direction) {
	this->sliding = true;
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->sliding = true;
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

Luigi::Luigi() : Character(3.0f) {
	
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
		character->SlidePipe(character->slideDirection);
	}
	else {
		character->control(true);
		character->accelerate(Vector2{ character->accX, GRAVITY }, deltaTime);
	}
	character->Update(deltaTime);
}
void InHole::execute(float deltaTime) {
	character->control(false);
	character->setVelocity( Vector2{0.0f, 700.0f} );
	character->Update(deltaTime);
};

AutoMove* AutoMove::instance = nullptr;
void AutoMove::execute(float deltaTime) {
if (totalTime < 5.0f) {
	character->control(false);
	character->accelerate(Vector2{ ACC_X, GRAVITY }, deltaTime);
	character->Update(deltaTime);
	totalTime += deltaTime;
	std::cout << totalTime;
}
else {
	character->setWin();
	character->control(false);
	character->setVelocity(Vector2{ 0.0f, 0.0f });
	character->Update(deltaTime);
}
}