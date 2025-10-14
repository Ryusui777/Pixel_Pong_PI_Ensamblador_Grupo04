#pragma once
#include "shared.h"

class Bot {
    private:
        const char* bot_path = "res/mainGame/player_yellow.png";
        Texture2D texture;
        Vector2 position;
    public:
        /**
         * @brief Carga la textura el bot,
         * y lo pone en su posicion original
         */
        void init();
        void move();
        void draw();
        void getRectangle(Rectangle&);
            
        
};