#pragma once
#include "raylib.h"
#include "shared.h"
#include <stdio.h>

const Vector2 homePos = {
    .x = WIDTH/2.0f,
    .y = HEIGHT/2.0f + 60
};
const Vector2 resumePos= {
    .x = WIDTH/2.0f,
    .y = HEIGHT/2.0f - 60
};
const Vector2 pausePos={
    .x = WIDTH/2.0f,
    .y = 25.0f
};


class Button{
    private:
        Vector2 position; // Posicion del boton
        Texture2D texture; // textura del boton
    public:
        /**
         * @brief Construct a new Button object
         */
        Button();
        /**
         * @brief Carga la textura del boton y su
         * posicion inicial
         */
        void init(char*, Vector2);

        /**
         * @brief Dibuja el boton en pantalla
         */
        void draw();

        /**
         * @brief Determina si el mouse esta en el area del boton

         * @return int 1 si el mouse esta en el area del boton 0 si no
         */
        int isHovered();

        /**
         * @brief  Determina si el boton esta siendo presionado,
         * si ya fue presionado y el usuario mantiene presionado
         * solo se activa una vez
         * 
         * @return int 1 si fue presionado 0 si no
         */
        int isClicked(){
            return isHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        }

};
