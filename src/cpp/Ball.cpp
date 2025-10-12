#include "Ball.h"
#include <cmath>


extern "C" void pelotaReverseY(float*);
extern "C" void pelotaReverseX(float*);
void Ball::init(){
    this->texture = LoadTexture((char*)ball_path);
    this->speed = 5.0f;  // Velocidad inicial
    reset();
}

void Ball::reset(){
    position.x = WIDTH/2.0f;
    position.y = HEIGHT/2.0f;
    
    // Dirección inicial aleatoria
    float angle = GetRandomValue(0, 1) ? 45.0f : 135.0f; // 45° o 135°
    velocity.x = cos(angle * DEG2RAD) * speed;
    velocity.y = sin(angle * DEG2RAD) * speed;
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
    position.x += velocity.x;
    position.y += velocity.y;
    
    // Verificar colisiones con los bordes
    checkBoundaryCollision();
}

void Ball::checkBoundaryCollision(){
    float halfWidth = getWidth() / 2;
    float halfHeight = getHeight() / 2;
    
    // Colisión con bordes superior e inferior
    if (position.y - halfHeight <= 0 || position.y + halfHeight >= HEIGHT) {
        reverseY();
    }
    
    // Colisión con bordes izquierdo y derecho
    if (position.x - halfWidth <= 0 || position.x + halfWidth >= WIDTH) {
        // manejar el punto
        reset(); 
    }
}

void Ball::reverseX(){
    pelotaReverseX(&velocity.y);
}

void Ball::reverseY(){
    pelotaReverseY(&velocity.y);
}