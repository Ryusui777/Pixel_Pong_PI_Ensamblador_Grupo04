#include "MainGame.h"


void MainGame::init(){
    // Inicializacion de lo elementos
    this->player.init();
    this->bot.init();
    this->pause.init((char*)pausePath, pausePos);

    // Dice que la escena es interactuable
    this->interactable = 1;
}

void MainGame::updateElements(){
    this->player.move();
    if(pause.isClicked()) printf("El boton de pausa fue presionado\n");
}

void MainGame::draw(){
    if(interactable) updateElements();
    this->player.draw();
    this->bot.draw();
    this->pause.draw();
}

void MainGame::isPaused(std::uint8_t& paused){
    paused = (this->pause.isClicked())? 1 : paused;
}
