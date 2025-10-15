// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Label.h"

void Label::initializeLabel(char* path, Vector2 position) {
  this->texture = LoadTexture(path);
  SetTextureFilter(texture, TEXTURE_FILTER_POINT);
  this->position = position;
}

void Label::drawLabel() {
  Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };
  Rectangle dst{ position.x, position.y,
    texture.width * SCALE, texture.height * SCALE };
  Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
  DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}
