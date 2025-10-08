#include <stdio.h>
#include "Window.h"
#include "MainGame.h"
#include "Menu.h"

int main(){
    // Componentes
    Window window;
    MainGame* mainGame = new MainGame;
    Menu* menu = new Menu;
    

    // Inicializacion de componentes
    window.init();
    mainGame->init();
    menu->init();

    // Ciclo del juego
    std::uint8_t paused = 0;


    while(!WindowShouldClose()){
        window.beginDraw();
        //? Todo el resto de componentes se renderizan en este periodo

        mainGame->isPaused(paused);
        mainGame->switchInteractable();
        
        mainGame->draw();
        if(paused) menu->draw();
        //?
        window.endDraw();
    }
    delete mainGame;
    delete menu;

    window.kill(); // Cierra la vantana

    return 0;
}

