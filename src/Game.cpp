// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Game.h"

void Game::updateElements() {
  this->player.movePlayer();
  this->ball.moveBall();
}

void Game::initializeGame() {
  // Inicializacion de los elementos
  this->player.initializePlayer();
  this->bot.initializeBot();
  this->ball.initializeBall();
  this->pause_button.initializeButton((char*)pause_button_path, pause_button_pos);

  // Dice que la escena es interactuable
  this->interactable = 0;
}

void Game::drawGameElements() {
  if (interactable) updateElements();
  this->ball.drawBall();
  this->player.drawPlayer();
  this->bot.drawBot();
  this->pause_button.drawButton();
}

void Game::isGamePaused(byte& paused) {
  paused = (this->pause_button.isButtonBeingClicked()) ? 1 : paused;
  if (IsKeyDown(KEY_SPACE)) paused = 1;
}

void Game::resetMatch() {
  this->player.resetPlayerPosition();
  this->ball.resetBallPosition();
}
