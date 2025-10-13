// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Player.h"

extern "C" void moverJugadorArriba();
extern "C" void moverJugadorAbajo();
extern "C" void initPlayerMovement(float, float, Vector2*);

void Player::init() {
  // Carga la textura del jugador
  this->texture = LoadTexture(PLY_PATH);
  SetTextureFilter(texture, TEXTURE_FILTER_POINT);

  // Configura los limites de la pantalla
  const float halfH = (texture.height * SCALE) * 0.5f;
  const float upperLimit = 0.0f + halfH;
  const float lowerLimit = (float)GetScreenHeight() - halfH;
  initPlayerMovement(upperLimit, lowerLimit, &position);
  reset();
}

void Player::moveDown() {
  moverJugadorAbajo();
}

void Player::moveUP() {
  moverJugadorArriba();
}

void Player::move() {
  if (IsKeyDown(KEY_DOWN)) moveDown();
  if (IsKeyDown(KEY_UP)) moveUP();
}

void Player::draw() {
  Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };
  Rectangle dst{ position.x, position.y,
    texture.width * SCALE, texture.height * SCALE };
  Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
  DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void Player::reset() {
  // Centra el jugador
  const float margin = 5.0f;
  position.y = WINDOW_HEIGHT / 2.0f;
  position.x = WINDOW_WIDTH - texture.width * SCALE - margin;
}
