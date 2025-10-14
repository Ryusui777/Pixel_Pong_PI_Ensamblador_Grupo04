#pragma once 
#include "raylib.h"
#include "shared.h"
#include <stdio.h>

#define SPEED 8
#define PLY_PATH (char*)"res/mainGame/player_red.png"



class Player{
    private:

        Vector2 position; // Posicion del jugador
        Texture2D texture; // textura del jugador
        void moveDown();
        void moveUP();

    public:
        void move();
        /**
         * @brief Inicializa el jugador, carga su textura, y
         * posicion inicial. Esta debe ser llamada despues de
         * inicializar la pantalla de otra manera habra un error.
         */
        void init();
        /**
         * @brief Renderiza el jugador en pantalla
         */
        void draw();
        /**
         * @brief 
         */
        void reset();

        /**
         * @brief Get the Rectangle object
         */
        void getRectangle(Rectangle&);

};