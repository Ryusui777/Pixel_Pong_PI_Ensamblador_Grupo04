// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Game.h"

void Game::updateElements() {
  this->player.move();
  this->ball.move();
}

void Game::initializeGame() {
  // Inicializacion de los elementos
  this->player.init();
  this->bot.init();
  this->ball.init();
  this->pause.init((char*)pause_button_path, pausePos);

  // Dice que la escena es interactuable
  this->interactable = 0;
}

void Game::drawGameElements() {
  if (interactable) updateElements();
  this->ball.draw();
  this->player.draw();
  this->bot.draw();
  this->pause.draw();
}

void Game::isGamePaused(byte& paused) {
  paused = (this->pause.isClicked()) ? 1 : paused;
  if (IsKeyDown(KEY_SPACE)) paused = 1;
}

void Game::resetMatch() {
  this->player.reset();
  this->ball.reset();
}
