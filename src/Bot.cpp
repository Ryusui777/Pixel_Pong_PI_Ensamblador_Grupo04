// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Bot.h"
#include <iostream>

extern "C" void initBotMovement(float, float, Vector2*, Vector2*, Vector2*);
extern "C" void moverBot();

void Bot::initializeBot(Ball* ball) {
  // Carga la textura del bot
  this->texture = LoadTexture((char*)bot_path);
  SetTextureFilter(texture, TEXTURE_FILTER_POINT);

  resetBot();

  // Configura los limites de la pantalla
  const float halfH = (texture.height * SCALE) * 0.5f;
  const float upperLimit = 0.0f + halfH;
  const float lowerLimit = (float)WINDOW_HEIGHT - halfH;
  this->ballPositionPtr = &ball->position;
  this->ballVelocityPtr = &ball->velocity;
  // Se llama a la función de ensamblador
  initBotMovement(upperLimit, lowerLimit, &position, ballPositionPtr, ballVelocityPtr);
}

// Dibujar al bot
void Bot::drawBot() {
  Rectangle src{0, 0, (float)texture.width, (float)texture.height};
  Rectangle dst{position.x, position.y,
    texture.width * SCALE, texture.height * SCALE };
  Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
  DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

// Se llama desde Game
void Bot::moveBot() {
    moverBot();
    
}


void Bot::resetBot() {
  // Centra el bot
  const float margin = 5.0f;
  position.y = WINDOW_HEIGHT / 2.0f;
  position.x = texture.width * SCALE + margin;
}

Rectangle Bot::getRectangle() {
  Rectangle rect;
  float w = texture.width * SCALE;
  float h = texture.height* SCALE;
  rect.x = position.x - w * 0.5f;
  rect.y = position.y - h * 0.5f;
  rect.height = h;
  rect.width = w;
  return rect;
}
