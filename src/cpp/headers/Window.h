// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include <iostream>
#include "shared.h"

/**
 * @brief
 */
class Window {
 private:
  // Fondo de la ventana
  const char* bg_path = "res/Game_BG.png";
  Texture2D bg;

  int width;
  int height;

  /**
   * @brief Dibuja el background del juego
   */
  void drawBG();
 public:
  void init();  // Iniciar ventana
  void beginDraw();
  void endDraw();
  void draw(Texture2D, Vector2);
  void kill() {
    CloseWindow();
  }
};
