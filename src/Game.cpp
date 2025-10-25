// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Game.h"

void Game::updateElements() {
  this->player.movePlayer();
  this->ball.moveBall();
  this->bot.moveBot();
}

void Game::initializeGame() {
  // Inicializacion de los elementos
  this->player.initializePlayer();
  this->bot.initializeBot();
  this->ball.initializeBall();
  this->pause_button.initializeButton((char*)pause_button_path
    , pause_button_pos);

  // Dice que la escena es interactuable
  this->interactable = 0;
}

void Game::drawGameElements() {
  if (interactable) updateElements();
  this->ball.drawBall();
  this->player.drawPlayer();
  this->bot.drawBot();
  this->pause_button.drawButton();

  // Chequea colision con jugador
  if (CheckCollisionRecs(player.getRectangle(), ball.getRect())
    && !ball.isOpposing()) {
    ball.rebotarContraJugador();
  } else {  // Chequea colosion con bot
    if (CheckCollisionRecs(bot.getRectangle(), ball.getRect())
      && ball.isOpposing()) {
      ball.rebotarContraBot();
    }
  }

  // Informacion para debuggear
  if (DEBUG_MODE) {
    Rectangle r;

    r = player.getRectangle();
    DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);

    r = ball.getRect();
    DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);

    r = bot.getRectangle();
    DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);

    if (ball.isOpposing()) {
       printf("Ball is opposing player\n");
    } else {
      printf("Ball is not opposing player\n");
    }
  }
}

// Pausar juego
void Game::isGamePaused(byte& paused) {
  // Si se toca botón de pausa, pausamos
  paused = (this->pause_button.isButtonBeingClicked()) ? 1 : paused;
  // Pero también, si tocamos espacio, pausamos
  if (IsKeyDown(KEY_SPACE)) paused = 1;
}

void Game::resetMatch() {
  this->player.resetPlayerPosition();
  this->bot.resetBot();
  this->ball.resetBallPosition();
}
