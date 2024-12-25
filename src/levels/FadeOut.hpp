#pragma once
#include "raylib.h"
class FadeOut {
    protected:
        FadeOut() : m_Activated(false), m_Finished(false), m_Alpha(0.0f) {
            m_Duration = 1.5f;
            m_FadeSpeed = 1 / m_Duration;
        }
        ~FadeOut() = default;
    public:
        static FadeOut& getInstance() {
            static FadeOut instance;
            return instance;
        }
        void update();
        void render();
        void reset();
        bool isActivated();
        bool isFinished();
        void activate();
        void setFadeSpeed(float speed) { m_FadeSpeed = speed; }
        void setRectangle(Rectangle rectangle) { m_Rectangle = rectangle; }
        void setPos(Vector2 pos) { m_Rectangle.x = pos.x;}
        void setDuration(float duration) { m_Duration = duration; }
    private:
        float m_Duration;
        bool m_Activated;
        bool m_Finished;
        float m_Alpha;
        float m_FadeSpeed;
        Rectangle m_Rectangle = {0, -2000, 1024 * 2, 768 * 2};
};