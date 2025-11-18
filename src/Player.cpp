// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Player.h"

extern "C" void moverJugadorArriba();
extern "C" void moverJugadorAbajo();
extern "C" void initPlayerMovement(float, float, Vector2*);

void Player::initializePlayer() {
  arduino.connect("/dev/ttyACM0");
  // Carga la textura del jugador
  this->texture = LoadTexture(PLAYER_ASSET_PATH);
  SetTextureFilter(texture, TEXTURE_FILTER_POINT);

  // Configura los limites de la pantalla
  const float halfH = (texture.height * SCALE) * 0.5f;
  const float upperLimit = 0.0f + halfH;
  const float lowerLimit = (float)GetScreenHeight() - halfH;
  // Se llama a la función de ensamblador
  initPlayerMovement(upperLimit, lowerLimit, &position);
  resetPlayerPosition();
}

// Se llama a la función de ensamblador
void Player::movePlayerDown() {
  moverJugadorAbajo();
}

// Se llama a la función de ensamblador
void Player::movePlayerUp() {
  moverJugadorArriba();
}

void Player::drawPlayer() {
  Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };
  Rectangle dst{ position.x, position.y,
    texture.width * SCALE, texture.height * SCALE };
  Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
  DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void Player::movePlayer() {
  // if (IsKeyDown(KEY_DOWN)) movePlayerDown();
  // if (IsKeyDown(KEY_UP)) movePlayerUp();

  if (IsKeyDown(KEY_DOWN)) movePlayerDown();  // teclas
  if (IsKeyDown(KEY_UP)) movePlayerUp();  // teclas

  // joystick
  char cmd = arduino.readCommand();
  if (cmd == 'U') movePlayerUp();
  if (cmd == 'D') movePlayerDown();
}


void Player::resetPlayerPosition() {
  // Centra el jugador
  const float margin = 5.0f;
  position.y = WINDOW_HEIGHT / 2.0f;
  position.x = WINDOW_WIDTH - texture.width * SCALE - margin;
}

Rectangle Player::getRectangle() {
  Rectangle rect;
  float w = texture.width * SCALE;
  float h = texture.height* SCALE;
  rect.x = position.x - w * 0.5f;
  rect.y = position.y - h * 0.5f;
  rect.height = h;
  rect.width = w;
  return rect;
}
