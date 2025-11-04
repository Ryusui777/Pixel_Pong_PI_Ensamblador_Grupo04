// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "shared.h"

/**
 * @brief para mostrar el logo
 */
class Label {
 private:
  Texture2D texture;
  Vector2 position;
 public:
  int getWidht(){
    return texture.width;
  }
  float getHeight(){
    return texture.height;

  }
  void initializeLabel(char*, Vector2);
  void drawLabel();
};
