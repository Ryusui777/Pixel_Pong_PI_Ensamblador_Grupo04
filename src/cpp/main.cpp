#include <stdio.h>
#include "Window.h"
#include "MainGame.h"
#include "Menu.h"
#include "HomeScreen.h"

int main(){
    // Componentes
    Window window;
    MainGame* mainGame = new MainGame;
    HomeScreen* homeScreen = new HomeScreen;
    Menu* menu = new Menu;
    

    // Inicializacion de componentes
    window.init();
    homeScreen->init();
    mainGame->init();
    menu->init();

    // Ciclo del juego
    std::uint8_t paused = 0;
    std::uint8_t inHome = 1;
    std::uint8_t ended = 0;
    std::uint8_t inGame = 0;


    while(!WindowShouldClose()){
        window.beginDraw();
        //? Todo el resto de componentes se renderizan en este periodo
        if(inHome){
            homeScreen->draw();
            homeScreen->started(inGame);
            inHome = (inGame)? 0 : 1;
        }
        else if(inGame){
            mainGame->setInteractable();
            mainGame->draw();
            mainGame->isPaused(paused);
            inGame = (paused)? 0 : 1;
            if(!inGame) mainGame->setNotInteractable();
        }
        else if(paused){
            mainGame->draw();
            menu->draw();
            menu->resumed(inGame);
            menu->goHome(inHome);
            paused = (inGame)? 0 : 1;
            if(paused) paused = (inHome)? 0 : 1;
            
        }

        
        //?
        window.endDraw();
    }
    delete mainGame;
    delete menu;
    delete homeScreen;

    window.kill(); // Cierra la vantana

    return 0;
}

