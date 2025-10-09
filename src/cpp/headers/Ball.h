#pragma once

#include "shared.h"



class Ball {
    private:
    const char* ball_path = "res/mainGame/ball.png";
    Texture2D texture;
    Vector2 position;
    public:
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
        void move();
        void reset();
};