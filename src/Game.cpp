// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Game.h"
#include <iostream>
#define PROBANDO 1
extern "C" void rebote_central();
extern "C" void rebote_superior();
extern "C" void rebote_inferior();
extern "C" void incrementar_velocidad();
extern "C" void setDifficulty(char);
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
  this->bot.initializeBot();
  this->ball.initializeBall();
  this->pause_button.initializeButton((char*)pause_button_path
    , pause_button_pos);

  #if PROBANDO
  this->marcadorBot.init({WINDOW_WIDTH/4, 30.0f});
  this->marcadorPly.init({(WINDOW_WIDTH/2 + WINDOW_WIDTH/4), 30.0f});
  #endif

  // Dice que la escena es interactuable
  this->interactable = 0;
}

void Game::checkCollisions(){

    Rectangle ball_rect = ball.getRect();
  if(!ball.isOpposing()){
    HitBox_t plyHitBox = player.getRectangle();

    if(CheckCollisionRecs(plyHitBox.upperHitBox, ball.getRect())){
        rebote_superior();

      }else if(CheckCollisionRecs(plyHitBox.lowerMiddleHitBox, ball.getRect())){
        rebote_central();

      }else if(CheckCollisionRecs(plyHitBox.upperMiddleHitBox, ball.getRect())){
        rebote_central();

      }else if(CheckCollisionRecs(plyHitBox.lowerHitBox, ball.getRect())){
        rebote_inferior();
      }
  }
  else{
    HitBox_t plyHitBox = bot.getRectangle();

    if(CheckCollisionRecs(plyHitBox.upperHitBox, ball.getRect())){
        rebote_superior();

      }else if(CheckCollisionRecs(plyHitBox.lowerMiddleHitBox, ball.getRect())){
        rebote_central();

      }else if(CheckCollisionRecs(plyHitBox.upperMiddleHitBox, ball.getRect())){
        rebote_central();

      }else if(CheckCollisionRecs(plyHitBox.lowerHitBox, ball.getRect())){
        rebote_inferior();
      }

  }



  // Informacion para debuggear
  if (DEBUG_MODE) {
    Rectangle r;

    r = player.getRectangle().upperHitBox;
    DrawRectangleLines(r.x, r.y, r.width, r.height, RED);
    r = player.getRectangle().upperMiddleHitBox;
    DrawRectangleLines(r.x, r.y, r.width, r.height, BLUE);
    r = player.getRectangle().lowerMiddleHitBox;
    DrawRectangleLines(r.x, r.y, r.width, r.height, YELLOW);
    r = player.getRectangle().lowerHitBox;
    DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);


    r = ball.getRect();
    DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);

    r = bot.getRectangle().upperHitBox;
    DrawRectangleLines(r.x, r.y, r.width, r.height, RED);
    r = bot.getRectangle().upperMiddleHitBox;
    DrawRectangleLines(r.x, r.y, r.width, r.height, BLUE);
    r = bot.getRectangle().lowerMiddleHitBox;
    DrawRectangleLines(r.x, r.y, r.width, r.height, YELLOW);
    r = bot.getRectangle().lowerHitBox;
    DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);

  }

}
void Game::drawGameElements(SoundManager* soundManager) {
  if (interactable) updateElements(soundManager);
  this->ball.drawBall();
  this->player.drawPlayer();
  this->bot.drawBot();
  this->pause_button.drawButton();

  this->marcadorBot.draw(getBotScore());
  this->marcadorPly.draw(getPlyScore());

  checkCollisions();
  static int lastTick = -1;
  int t = (int)GetTime();
  if (t % 2 == 0 && t != lastTick) {
    incrementar_velocidad();
    lastTick = t;
  }

  if(IsKeyDown(KEY_B)) setDifficulty(0); // Easy
  if(IsKeyDown(KEY_N)) setDifficulty(1); // Medium
  if(IsKeyDown(KEY_M)) setDifficulty(2); // Hard
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
