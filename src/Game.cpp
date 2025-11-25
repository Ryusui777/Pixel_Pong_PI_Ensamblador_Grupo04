// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Game.h"
#include "Bot.h"
extern "C" int getPlyScore();
extern "C" int getBotScore();
extern "C" void resetScore();

void Game::updateElements(SoundManager* soundManager) {
  this->player.movePlayer();
  this->ball.moveBall();
  this->bot.moveBot();
}

void Game::initializeGame() {
  // Inicializacion de los elementos
  this->player.initializePlayer();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Develop
  
  this->ball.initializeBall();

  this->bot.initializeBot(&this->ball);

  this->ball.resetBallPosition();
<<<<<<< HEAD
=======

  this->ball.initializeBall();
  this->bot.initializeBot(&ball);
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
=======
  
  this->ball.initializeBall();
=======
  
  this->ball.initializeBall();
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)

  this->bot.initializeBot(&this->ball);

  this->ball.resetBallPosition();
<<<<<<< HEAD
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
=======

  this->ball.initializeBall();
  this->bot.initializeBot(&ball);
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
=======
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
=======
>>>>>>> Develop
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

void Game::isGamePaused(byte& paused) {
  paused = (this->pause_button.isButtonBeingClicked()) ? 1 : paused;
  if (IsKeyDown(KEY_SPACE)) paused = 1;
}

void Game::resetMatch() {
  this->player.resetPlayerPosition();
  this->bot.resetBot();
  this->ball.resetBallPosition();
}
