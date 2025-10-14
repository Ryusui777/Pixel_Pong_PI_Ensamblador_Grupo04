#include "Ball.h"
#include <cmath>

extern "C" void initPelotaMovement(Vector2*, Vector2*, float, float);
extern "C" void pelotaReverseY();
extern "C" void pelotaReverseX();
extern "C" void pelotaMove();
extern "C" void resetBall();
extern "C" void pelotaReboto();

void Ball::init(){
    this->texture = LoadTexture((char*)ball_path);
    this->speed = 10.0f;  // Velocidad inicial

    // Define limites inferior y superior
    float upperLimt = getHeight() / 2.0f;
    float lowerLimit = HEIGHT - (getHeight() / 2.0f);
    initPelotaMovement(&velocity, &position, upperLimt, lowerLimit);

    reset();
}

void Ball::reset(){
    position.x = WIDTH/2.0f;
    position.y = HEIGHT/2.0f;
    
    resetBall();

}

void Ball::draw(){
    Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };
    Rectangle dst{ position.x, position.y,
                   texture.width * SCALE, texture.height * SCALE };
    Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void Ball::move(){
    // Actualizar posición
    pelotaMove();
    
    // Verificar colisiones con los bordes
    checkBoundaryCollision();
}

void Ball::checkBoundaryCollision(){
    float halfWidth = getWidth() / 2;
    float halfHeight = getHeight() / 2;
    
    // Colisión con bordes superior e inferior
    if (position.y - halfHeight <= 0 || position.y + halfHeight >= HEIGHT) {
        pelotaReverseY();
    }
    
    // Colisión con bordes izquierdo y derecho
    if (position.x - halfWidth <= 0 || position.x  >= WIDTH) {
        // manejar el punto
        reset(); 
    }
}
void Ball::rebotarContraJugador(){
    reverseX();
    pelotaReboto();
}
void Ball::rebotarContraBot(){
    reverseX();
    pelotaReboto();
}

void Ball::reverseX(){
    pelotaReverseX();
}

void Ball::reverseY(){
    pelotaReverseY();
}