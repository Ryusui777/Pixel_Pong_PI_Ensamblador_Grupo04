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

    
    // Chequea colision con jugador
    if(CheckCollisionRecs(player.getRectangle(), ball.getRect()) && !ball.isOpposing()){
        ball.rebotarContraJugador();
    }

    // Informacion para debuggear
    if(DEBUG_MODE){
        Rectangle r;
        r = player.getRectangle();
        DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);
        r = ball.getRect();
        DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);
        if(ball.isOpposing()) printf("Ball is opposing player\n");
        else printf("Ball is not opposing player\n");
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
