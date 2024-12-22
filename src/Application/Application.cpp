// Application.cpp
#include "Application.hpp"

Application::Application() {
    currentState = new MenuState();
}

Application::~Application() {
    delete currentState;
}

void Application::setState(State* state) {
    delete currentState;
    currentState = state;
}

void Application::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        currentState->handle(*this);
        EndDrawing();
    }
    CloseWindow();
}