#include "MainGame.h"


void MainGame::init(){
    // Inicializacion de lo elementos
    this->player.init();
    this->bot.init();
    this->ball.init();
    this->pause.init((char*)pausePath, pausePos);

    // Dice que la escena es interactuable
    this->interactable = 0;
}

void MainGame::updateElements(){
    this->player.move();
    this->ball.move();
    
}

void MainGame::draw(){
    if(interactable) updateElements();
    this->ball.draw();
    this->player.draw();
    this->bot.draw();
    this->pause.draw();

    Rectangle r;
    player.getRectangle(r);
    
    if(CheckCollisionRecs(r, ball.getRect()) && !ball.isOpposing()) ball.reverseX();
    if(DEBUG_MODE){
        DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);
        r = ball.getRect();
        DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);
    }

    
}

void MainGame::isPaused(byte& paused){
    paused = (this->pause.isClicked())? 1 : paused;
    if(IsKeyDown(KEY_SPACE)) paused = 1;
}

void MainGame::reset(){
    this->player.reset();
    this->ball.reset();
}
