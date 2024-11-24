
#ifndef Application_hpp
#define Application_hpp

#include "GUI.hpp"

class Menu {
private:
    PlayButton play;
    SettingButton setting;
    HighScoreButton highScore;
    InforButton infor;
public:
    Menu();
    void draw();
    void hanlde();
    int8_t clicked();
};



class Application {
private:
    int tab;
public:
    Application(): tab(0) {}
    void run();
    int menu();
};

#endif /* Application_hpp */
