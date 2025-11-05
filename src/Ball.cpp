// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Ball.h"
#include <cmath>

void Ball::initializeBall() {
  this->texture = LoadTexture((char*)ball_path);
  this->speed = 10.0f;  // Velocidad inicial

  // Define limites inferior y superior
  float upperLimt = getBallHeight() / 2.0f;
  float lowerLimit = WINDOW_HEIGHT - (getBallHeight() / 2.0f);
  initPelotaMovement(&velocity, &position, upperLimt, lowerLimit);

  resetBallPosition();
}

void Ball::resetBallPosition() {
  position.x = WINDOW_WIDTH/2.0f;
  position.y = WINDOW_HEIGHT/2.0f;
  resetBall();
}

void Ball::drawBall() {
  Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };
  Rectangle dst{ position.x, position.y,
    texture.width * SCALE, texture.height * SCALE };
  Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
  DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void Ball::moveBall(SoundManager* soundManager) {
  // Actualizar posición
  pelotaMove();
  // Verificar colisiones con los bordes
  checkBoundaryCollision(soundManager);
}

void Ball::checkBoundaryCollision(SoundManager* soundManager) {
  float halfWidth = getBallWidth() / 2;
  float halfHeight = getBallHeight() / 2;

  // Colisión con bordes superior e inferior
  if (position.y - halfHeight <= 0 || position.y + halfHeight
    >= WINDOW_HEIGHT) {
    pelotaReverseY();
    if (soundManager) {
      soundManager->playWallHit();  // Sonido de golpe con muro
    }
  }

  // Anotación de punto
  if (position.x - halfWidth <= 0) {
    anotacion();
    soundManager->playBotScore();
    
    resetBallPosition();
  } else if (position.x + halfWidth >= WINDOW_WIDTH) {
    anotacion();
    soundManager->playPlayerScore();
    resetBallPosition();
  }
}

void Ball::rebotarContraJugador(SoundManager* soundManager) {
  reverseHorizontalTrajectory();
  pelotaReboto();
  if (soundManager) {
    soundManager->playPaddleHit();  // Sonidito
  }
}

void Ball::rebotarContraBot(SoundManager* soundManager) {
  reverseHorizontalTrajectory();
  pelotaReboto();
  if (soundManager) {
    soundManager->playPaddleHit();  // Sonidito
  }
}

void Ball::reverseHorizontalTrajectory() {
  pelotaReverseX();
}

void Ball::reverseVerticalTrajectory() {
  pelotaReverseY();
}
