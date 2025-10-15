#include "MainGame.h"

void MainGame::init(){
    // Inicializacion de lo elementos
    this->player.init();
    this->bot.initializeBot();
    this->ball.init();
    this->pause.initializeButton((char*)pausePath, pause_button_pos);

    // Dice que la escena es interactuable
    this->interactable = 0;
}

void MainGame::updateElements(){
    this->player.move();
    this->ball.move();
    this->bot.moveBot();
    
}

void MainGame::draw(){
    if(interactable) updateElements();
    this->ball.draw();
    this->player.draw();
    this->bot.drawBot();
    this->pause.drawButton();

    
    // Chequea colision con jugador
    if(CheckCollisionRecs(player.getRectangle(), ball.getRect()) && !ball.isOpposing()){
        ball.rebotarContraJugador();
    }
    // Chequea colosion con bot
    else{
        if(CheckCollisionRecs(bot.getRectangle(), ball.getRect()) && ball.isOpposing()){
            ball.rebotarContraBot();
        }
    }

    // Informacion para debuggear
    if(DEBUG_MODE){
        Rectangle r;

        r = player.getRectangle();
        DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);

        r = ball.getRect();
        DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);

        r = bot.getRectangle();
        DrawRectangleLines(r.x, r.y, r.width, r.height, WHITE);

        if(ball.isOpposing()) printf("Ball is opposing player\n");
        else printf("Ball is not opposing player\n");
    }

    
}

void MainGame::isPaused(byte& paused){
    paused = (this->pause.isButtonBeingClicked())? 1 : paused;
    if(IsKeyDown(KEY_SPACE)) paused = 1;
}

void MainGame::reset(){
    this->player.reset();
    this->bot.resetBot();
    this->ball.reset();
}
