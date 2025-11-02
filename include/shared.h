// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include <stdio.h>
#include <cstdint>
#include "raylib.h"
#define WINDOW_WIDTH 256*5
#define WINDOW_HEIGHT 144*5
#define SCALE 5.0f
#define DEBUG_MODE 1
typedef std::uint8_t byte;

typedef struct {
    Rectangle upperHitBox;
    Rectangle upperMiddleHitBox;
    Rectangle lowerMiddleHitBox;
    Rectangle lowerHitBox;
} HitBox_t;
