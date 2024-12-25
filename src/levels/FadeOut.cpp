#include "FadeOut.hpp"
#include <iostream>
void FadeOut::render() {
    // std::cout << "Is Activated: " << m_Activated << std::endl;
    if (m_Activated) {
        // std::cout << "Rendering" << std::endl;
        // std::cout << "Rectangle: " << m_Rectangle.x << " " << m_Rectangle.y << " " << m_Rectangle.width << " " << m_Rectangle.height << std::endl;
        DrawRectangleRec(m_Rectangle, ColorAlpha(BLACK, m_Alpha));
    }
}
void FadeOut::update() {
    if (IsKeyPressed(KEY_Y))
    {
        activate();
    }
    float DeltaTime = GetFrameTime();
    if (m_Activated) {
        m_Alpha += m_FadeSpeed * DeltaTime;
        if (m_Alpha >= m_Duration) {
            m_Finished = true;
            // m_Activated = false;
        }
    }
}
void FadeOut::reset() {
    m_Activated = false;
    m_Finished = false;
    // m_Duration = 5.0f;
    m_Alpha = 0.0f;
}
void FadeOut::activate() {
    m_Activated = true;
    std::cout << "Activated" << std::endl;
}
bool FadeOut::isActivated() {
    return m_Activated;
}
bool FadeOut::isFinished() {
    return m_Finished;
}

