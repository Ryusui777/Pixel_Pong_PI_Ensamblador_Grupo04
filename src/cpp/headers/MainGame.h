#pragma once
#include "shared.h"
#include "Player.h"
#include "Button.h"
#include "Bot.h"
#include "Ball.h"

class MainGame {
    private:
        const char* pausePath="res/mainGame/pause.png";

        Player player;
        Bot bot;
        Ball ball;
        Button pause;


        std::uint8_t interactable;

        void updateElements();

    public:
        /**
         * @brief Inicia los elementos de la clase,
         * carga sus texturas y posiciones.
         */
        void init();
        /**
         * @brief Rederiza el juego principal en pantalla.
         */
        void draw();
        /**
         * @brief Cambia el estado del juego,
         * si la varible que cambia esta en 0
         * entonces los componentes se vuelven
         * no interactuales.
         */
        void setInteractable(){
            interactable = 1;
        }
        void setNotInteractable(){
            interactable = 0;
        }

        void isPaused(byte&);

        void reset();

        
};