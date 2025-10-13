// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Ball.h"
#include <cmath>

extern "C" void initPelotaMovement(Vector2*, Vector2*, float, float);
extern "C" void pelotaReverseY();
extern "C" void pelotaReverseX();
extern "C" void pelotaMove();

void Ball::init() {
  this->texture = LoadTexture((char*)ball_path);
  this->speed = 5.0f;  // Velocidad inicial

  // Define limites inferior y superior
  float upperLimt = getHeight() / 2.0f;
  float lowerLimit = WINDOW_HEIGHT - (getHeight() / 2.0f);
  initPelotaMovement(&velocity, &position, upperLimt, lowerLimit);

  reset();
}

void Ball::reset() {
  position.x = WINDOW_WIDTH/2.0f;
  position.y = WINDOW_HEIGHT/2.0f;

  // Dirección inicial aleatoria
  float angle = GetRandomValue(0, 1) ? 45.0f : 135.0f;  // 45° o 135°
  velocity.x = cos(angle * DEG2RAD) * speed;
  velocity.y = sin(angle * DEG2RAD) * speed;
}

void Ball::draw() {
  Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };
  Rectangle dst{ position.x, position.y,
    texture.width * SCALE, texture.height * SCALE };
  Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
  DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void Ball::move() {
  // Actualizar posición
  pelotaMove();
  // Verificar colisiones con los bordes
  checkBoundaryCollision();
}

void Ball::checkBoundaryCollision() {
  float halfWidth = getWidth() / 2;
  float halfHeight = getHeight() / 2;

  // Colisión con bordes superior e inferior
  if (position.y - halfHeight <= 0 || position.y + halfHeight >= WINDOW_HEIGHT) {
    pelotaReverseY();
  }

  // Colisión con bordes izquierdo y derecho
  if (position.x - halfWidth <= 0 || position.x + halfWidth >= WINDOW_WIDTH) {
    // manejar el punto
    reset();
  }
}

void Ball::reverseX() {
  pelotaReverseX();
}

void Ball::reverseY() {
  pelotaReverseY();
}
