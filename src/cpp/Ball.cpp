#include "Ball.h"



void Ball::init(){
    this->texture = LoadTexture((char*)ball_path);
    reset();
}

void Ball::reset(){
    position.x = WIDTH/2.0f;
    position.y = HEIGHT/2.0f;
}

void Ball::draw(){
    Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };
    Rectangle dst{ position.x, position.y,
                   texture.width * SCALE, texture.height * SCALE };
    Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}