// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "MainGame.h"

void MainGame::init() {
  // Inicializacion de lo elementos
  this->player.init();
  this->bot.init();
  this->ball.init();
  this->pause.init((char*)pausePath, pausePos);

  // Dice que la escena es interactuable
  this->interactable = 0;
}

void MainGame::updateElements() {
  this->player.move();
  this->ball.move();
}

void MainGame::draw() {
  if (interactable) updateElements();
  this->ball.draw();
  this->player.draw();
  this->bot.draw();
  this->pause.draw();
}

void MainGame::isPaused(byte& paused) {
  paused = (this->pause.isClicked()) ? 1 : paused;
  if (IsKeyDown(KEY_SPACE)) paused = 1;
}

void MainGame::reset() {
  this->player.reset();
  this->ball.reset();
}
