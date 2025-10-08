#pragma once
#include <cstdint>
#include <stdio.h>
#include "raylib.h"
#define WIDTH 256*5
#define HEIGHT 144*5
#define SCALE 5.0f


struct infoPartida{
    std::uint8_t pausado;
    std::uint8_t pts_ply;
    std::uint8_t pts_bot;
    int speed_ply;
    int speed_ball;
};

