#include "Character.h"
#include <iostream>

#define MAX_SPEED 700.0f
#define FAST_BRAKE 1400.0f
#define ACC_X 600.0f
#define SLOW_BRAKE 800.0f
#define GRAVITY 3500.0f

Character::Character(float jumpHeight) : firePool(nullptr)
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
	this->score = 0;
	if (this->firePool == nullptr) {
		this->firePool = new FirePool(2);
	}
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
		MusicManager::getInstance().PlayMusic(Invincible);
	}
	if (IsKeyPressed(KEY_L)) {
		killEnemy();
	}
	if (IsKeyPressed(KEY_Q)) {
		pullFlag = true;
	}
	if (IsKeyPressed(KEY_F1)) {
		MusicManager::getInstance().PlayMusic(OverWorld);
	}
	if (IsKeyPressed(KEY_F2)) {
		MusicManager::getInstance().PlayMusic(Origin_UnderWorld);
	}
	if (IsKeyPressed(KEY_F3)) {
		MusicManager::getInstance().PlayMusic(Invincible);
	}
	if (IsKeyPressed(KEY_F4)) {
		MusicManager::getInstance().PlayMusic(SuperBellHill);
	}
	if (IsKeyPressed(KEY_F5)) {
		MusicManager::getInstance().PlayMusic(FlowerGarden);
	}
	if (IsKeyPressed(KEY_F6)) {
		MusicManager::getInstance().PlayMusic(Athletic);
	}
	if (IsKeyPressed(KEY_F7)) {
		MusicManager::getInstance().PlayMusic(UnderGround);
	}
	if (IsKeyPressed(KEY_F8)) {
		MusicManager::getInstance().PlayMusic(SMB);
	}
	if (IsKeyPressed(KEY_F9)) {
		MusicManager::getInstance().StopMusic();
	}

	if (IsKeyPressed(KEY_SPACE) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
		SoundManager::getInstance().PlaySoundEffect(JUMP_SOUND);
	}
	if (form==2 && IsKeyPressed(KEY_M)) {
		fire = true;
		Vector2 direction = { 0,0 };
		if (faceRight) direction = { 1,0.3f };
		else direction = { -1,0.3f };
		Vector2 firePos = { position.x + size.x, position.y + size.y / 2 };
		firePool->GetAvailableFireBall(firePos, direction);
	}
		/*for (int i = 0; i < this->firePool->fireballs.size(); i++) {
			if (firePool->fireballs[i].IsActive()) {
				if (firePool->fireballs[i].getPosition().y > 600.0f) {
					firePool->fireballs[i].Bounce();
					std::cout << "bounce" << " ball " << i + 1 << std::endl;
				}
				if (firePool->fireballs[i].getPosition().x > 1200.0f) {
					firePool->fireballs[i].Deactivate();
					std::cout << "Deact" << std::endl;
				}
			}
		}*/
	// Deactivate if out of bounds

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
			MusicManager::getInstance().PlayMusic(OverWorld);
			isInvincible = false;
			InvincibleColor = WHITE;
			invincibleDuration = 6.0f;
		}
	}
	/*std::cout << "Size: " << size.x << " " << size.y << std::endl;
	std::cout << "scale: " << scale << std::endl;*/
}
void Character::hitFlag() {
	if (!pullFlag) {
		return;
	};
	float EndPosition = 700.0f - size.y;
	velocity.x = 0.0f;
	velocity.y = 300.0f;
	if (position.y >= EndPosition)
	{
		position.y = 700.0f-size.y;
		velocity.y = 0;
		if (faceRight) {
			position.x += size.x;
			faceRight = false;
		}
	}
}
void Character::setPullFlag(bool pullFlag) {
	if (pullFlag) MusicManager::getInstance().PlayMusic(FlagDown);	
	this->pullFlag = pullFlag;
	if (!this->pullFlag) {
		position.y = 750.0f - size.y;
	}
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
		SoundManager::getInstance().PlaySoundEffect(POWERDOWN_SOUND);
		return;
	}
	else {
		velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
		isDie = true;
		SoundManager::getInstance().PlaySoundEffect(DIE_SOUND);
	}
}
void Character::killEnemy() {
	velocity.y = -sqrtf(2.0f * GRAVITY * 50.0f);
	SoundManager::getInstance().PlaySoundEffect(KILL_SOUND);
}

void Character::reset() {
	position = { 20, 0 };
	velocity = { 0, 0 };
	accX = 0.0f;
	canJump = false;
	fire = false;
	brake = false;
	isDie = false;
	isChangingForm = false;
	isflicking = false;
	isInvincible = false;
	pullFlag = false;
	isWin = false;
	//powerDown();
	score = 0;
}
void Character::Draw()
{
	//std::cout << "Score" << score << std::endl;
	if (!isVisible) return;
	//std::cout << "velocity: " << velocity.x << " " << velocity.y << std::endl;
	Rectangle sourceRec = animation.uvRect; // The part of the texture to use for drawing
	Rectangle destRec = { position.x, position.y, fabs(sourceRec.width) * scale, sourceRec.height * scale }; // Destination rectangle with scaling
	float rotation = 0.0f;
	Vector2 origin = { 0.0f,0.0f };
	DrawTexturePro(textures[form], sourceRec, destRec, origin, rotation, InvincibleColor);
	firePool->Draw();

};

Mario::Mario() : Character(400.0f) {
	Chartype = MARIO;
	textures.push_back(LoadTexture("assets/textures/marioSmall3.png"));
	textures.push_back(LoadTexture("assets/textures/marioBig3.png"));
	textures.push_back(LoadTexture("assets/textures/marioFire3.png"));
	imageCounts.push_back({ 9,1 });
	imageCounts.push_back({ 8,1 });
	imageCounts.push_back({ 9,1 });
	float switchTime = 0.1f;
	animation = Animation(&textures[form], imageCounts[form], switchTime);
	size = { (float) textures[form].width / (imageCounts[form].x) * scale, (float)textures[form].height * scale};
	this->SlideDist = { size.x,size.y };
}
void Mario::Update(float deltaTime) {
	if (velocity.y > GRAVITY*deltaTime*1.2f) canJump = false; //handle double jump 

	if (pullFlag) state = 6;
	else if (velocity.x == 0.0f || sliding) {
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
	hitFlag();
	setPosition(Vector2{ position.x + velocity.x*deltaTime, position.y + velocity.y * deltaTime });
	firePool->Update();	
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

Luigi::Luigi() : Character(600.0f) {
	Chartype = LUIGI;
	textures.push_back(LoadTexture("assets/textures/luigiSmall.png"));
	textures.push_back(LoadTexture("assets/textures/luigiBig.png"));
	textures.push_back(LoadTexture("assets/textures/marioFire3.png"));
	imageCounts.push_back({ 9,1 });
	imageCounts.push_back({ 8,1 });
	imageCounts.push_back({ 9,1 });
	float switchTime = 0.1f;
	animation = Animation(&textures[form], imageCounts[form], switchTime);
	size = { (float)textures[form].width / (imageCounts[form].x) * scale, (float)textures[form].height * scale };
	this->SlideDist = { size.x,size.y };
	
}
void Luigi::Update(float deltaTime) {
	if (velocity.y > GRAVITY * deltaTime * 1.2f) canJump = false; //handle double jump 

	if (pullFlag) state = 6;
	else if (velocity.x == 0.0f || sliding) {
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
	hitFlag();
	setPosition(Vector2{ position.x + velocity.x * deltaTime, position.y + velocity.y * deltaTime });
	firePool->Update();
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
	if (!character->isPullFlag()) {
		if (totalTime == 0.0f) {
			MusicManager::getInstance().PlayMusic(LevelFinished);
		}
		if (MusicManager::getInstance().IsMusicPlaying() && totalTime >= 5.0f) {
			MusicManager::getInstance().StopMusic();
		}
		if (totalTime < 5.0) {
			character->control(false);
			character->setVelocity(Vector2{ 225.0f, 1.0f });
			character->Update(deltaTime);
			totalTime += deltaTime;
			//std::cout << totalTime;
		}
		else {
			character->setWin();
			character->control(false);
			character->setVelocity(Vector2{ 0.0f, 0.0f });
			character->Update(deltaTime);
		}
	}
	else {
		character->Update(deltaTime);
	}

}


//Backup 
//AutoMove* AutoMove::instance = nullptr;
//void AutoMove::execute(float deltaTime) {
//	if (totalTime == 0.0f) {
//		MusicManager::getInstance().PlayMusic(LevelFinished);
//	}
//	if (MusicManager::getInstance().IsMusicPlaying() && totalTime >= 5.0f) {
//		MusicManager::getInstance().StopMusic();
//	}
//	if (totalTime < 5.0f) {
//		character->control(false);
//		character->accelerate(Vector2{ ACC_X, GRAVITY }, deltaTime);
//		character->Update(deltaTime);
//		totalTime += deltaTime;
//		//std::cout << totalTime;
//	}
//	else {
//		character->setWin();
//		character->control(false);
//		character->setVelocity(Vector2{ 0.0f, 0.0f });
//		character->Update(deltaTime);
//	}
//}