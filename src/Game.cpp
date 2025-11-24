// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Game.h"
#include "Bot.h"
extern "C" int getPlyScore();
extern "C" int getBotScore();
extern "C" void resetScore();

void Game::updateElements(SoundManager* soundManager) {
  this->player.movePlayer();
  this->ball.moveBall(soundManager);
  this->bot.moveBot();
}

void Game::initializeGame() {
  // Inicializacion de los elementos
  this->player.initializePlayer();

  this->ball.initializeBall();
  this->bot.initializeBot(&ball);
  this->pause_button.initializeButton((char*)pause_button_path
    , pause_button_pos);
  this->marcadorBot.init({WINDOW_WIDTH/4, 30.0f});
  this->marcadorPly.init({(WINDOW_WIDTH/2 + WINDOW_WIDTH/4), 30.0f});

  // Dice que la escena es interactuable
  this->interactable = 0;
}

void Game::drawGameElements(SoundManager* soundManager) {
  if (interactable) updateElements(soundManager);
  this->ball.drawBall();
  this->player.drawPlayer();
  this->bot.drawBot();
  this->pause_button.drawButton();

  this->marcadorBot.draw(getBotScore());
  this->marcadorPly.draw(getPlyScore());
  // Chequea colision con jugador
  if (CheckCollisionRecs(player.getRectangle(), ball.getRect())
    && !ball.isOpposing()) {
    ball.rebotarContraJugador(soundManager);
  } else {  // Chequea colosion con bot
    if (CheckCollisionRecs(bot.getRectangle(), ball.getRect())
      && ball.isOpposing()) {
      ball.rebotarContraBot(soundManager);
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
void Game::isGamePaused(byte& paused, SoundManager* soundManager) {
  // Si se toca botón de pausa, pausamos
  paused = (this->pause_button.isButtonBeingClicked(soundManager)) ? 1 : paused;
  // Pero también, si tocamos espacio, pausamos
  if (IsKeyDown(KEY_SPACE)) paused = 1;
}

void Game::resetMatch() {
  this->player.resetPlayerPosition();
  this->bot.resetBot();
  this->ball.resetBallPosition();
  resetScore();
}
