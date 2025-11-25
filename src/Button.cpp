// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Button.h"

// Constructor
Button::Button() {}

// Inicializa un botón
void Button::initializeButton(char* imgPath, Vector2 vec) {
  position = vec;
  this->texture = LoadTexture(imgPath);
  SetTextureFilter(texture, TEXTURE_FILTER_POINT);
}

// Dibuja un botón
void Button::drawButton() {
  Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };
  Rectangle dst{ position.x, position.y,
  texture.width * 1.0f, texture.height * 1.0f};
  Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
  DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

// Verifica si el mouse está sobre un botón
byte Button::isMouseAboveButton() {
  // float scale = 5.0f;
  Rectangle dst{ position.x, position.y,
  texture.width * 1.0f, texture.height * 1.0f };
  Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
  Rectangle bounds{ dst.x - origin.x, dst.y - origin.y, dst.width, dst.height };
  Vector2 m = GetMousePosition();
  return CheckCollisionPointRec(m, bounds);
}
