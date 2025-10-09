#pragma once

#include "shared.h"



class Ball {
    private:
    const char* ball_path = "res/mainGame/ball.png";
    Texture2D texture;
    Vector2 position;
    public:
        void init();
        void draw();
        void move();
        void reset();
};