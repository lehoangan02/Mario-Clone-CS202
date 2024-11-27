//
//  Application.hpp
//  project
//
//  Created by Ngọc Bảo on 26/11/2024.
//

#ifndef Application_hpp
#define Application_hpp

#include "GUI.hpp"

class Application {
    private:
        int tab;
        Menu menu;
    public:
        Application() {
            tab = 0;
            menu = Menu();
        }
        void run();
        int handle();
};


#endif /* Application_hpp */
