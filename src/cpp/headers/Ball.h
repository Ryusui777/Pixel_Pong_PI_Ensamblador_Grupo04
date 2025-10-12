#pragma once

#include "shared.h"

class Ball {
private:
    const char* ball_path = "res/mainGame/ball.png";
    Texture2D texture;
    Vector2 position;
    Vector2 velocity;  
    float speed;       
    
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
    
    // metodos para manejar colisiones
    void checkBoundaryCollision();
    void reverseX();  // Invertir dirección X
    void reverseY();  // Invertir dirección Y
    
    // Getters para la posición y tamaño (necesarios para colisiones)
    Vector2 getPosition() const { return position; }
    float getWidth() const { return texture.width * SCALE; }
    float getHeight() const { return texture.height * SCALE; }
    Rectangle getRect() const { 
        return {position.x - getWidth()/2, position.y - getHeight()/2, getWidth(), getHeight()}; 
    }
};