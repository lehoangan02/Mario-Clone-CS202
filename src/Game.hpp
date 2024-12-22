
#ifndef GAME_hpp
#define GAME_hpp

#include "GUI.hpp"
#include "./characters/Character.h"
#include "./levels/Level.hpp"
#include "./animation/Animation.h"
#include "./Mediator/Mediator.hpp"
#include "ResourceManager.hpp"

class Game : public Mediator {
private:
    LevelFactory& factory;
    Level* level;
    Texture2D character;
    Character* player = nullptr;
    LEVEL_RETURN_MESSAGE state;
	Font myFont; //chau added this
	int countdown; //chau added this
	float timer;//chau added this
	std::vector<Texture2D> infoIcons;//chau added this
public:
    Game();
    Game(int characterMenu, int levelMenu);
    Game& operator=(const Game& other);
    Game(const Game& other);
    void start();
    void update(float deltaTime);
    void draw();

    void pause();
    void resume();
    void win();
    void lose();
    void quit();
    void nextLevel();
    void hiddenLevel();
    void restartLevel();

    // Implement notify method
    void notify(Component* sender, int eventCode) override;


    // Timer
	void resetCountdown();

    // Methods to handle game states
    void handleState();
    void drawPauseMenu();
    void drawContinueButton();
    void drawWinButton();
    void drawLoseButton();
    void drawQuitButton();
	void drawInfo(); // chau added this
	void DrawTextCentered(Font font, const std::string& label, const std::string& value, Vector2 position, float fontSize, float spacing, Color color); // chau added this
    LEVEL_RETURN_MESSAGE getState() { return state; };
};

#endif /* GAME_hpp */