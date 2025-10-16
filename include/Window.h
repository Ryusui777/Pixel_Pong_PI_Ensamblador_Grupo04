// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include <iostream>
#include "shared.h"

/**
 * @brief Clase responsable de generar la ventana de juego con su respectivo
 * fondo y fps.
 */
class Window {
 private:
  // Ruta a la imagen de fondo para la ventana de juego
  const char* game_background_path = "assets/game_background.png";
  Texture2D game_background;  // Fondo de la ventana

  /**
   * @brief Dibuja el fondo de la ventana
   */
  void drawWindowBackground();

 public:
  /**
   * @brief Inicializa la ventana con un ancho, alto, fondo, FPS y nombre
   * establecidos.
  */
  void initializeWindow();
  void beginWindowDraw();

  /**
   * @brief terminar de mostrar un frame.
   */
  void endWindowDraw();
  void killWindow() {
    CloseWindow();
  }
};
