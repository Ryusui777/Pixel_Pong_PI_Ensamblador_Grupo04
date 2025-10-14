// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "shared.h"

/**
 * @brief Clase encargada del movimiento del bot (jugador enemigo)
 */
class Bot {
 private:
  // Ruta a la textura del bot
//   const char* bot_path = "assets/mainGame/yellow_bot.png";
  const char* bot_path = "res/mainGame/player_yellow.png";
  Texture2D texture;  // Textura del bot
  Vector2 position;  // Posición del bot
 public:
  /**
   * @brief Carga la textura del bot y lo pone en su posición original
   */
  void init();

  /**
   * @brief dibuja textura del bot.
   */
  void draw();

  /**
   * @brief Mueve bot hacia arriba y abajo continuamente
   */
  void moveBot();

  void reset();

  Rectangle getRectangle();
  
};