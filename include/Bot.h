// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "shared.h"
#include "Ball.h"

/**
 * @brief Clase encargada del movimiento del bot (jugador enemigo)
 */
class Bot {
 private:
  // Ruta a la textura del bot
  const char* bot_path = "assets/mainGame/player_yellow.png";
  Texture2D texture;  // Textura del bot
  Vector2 position;  // Posición del bot
  Vector2* ballPositionPtr;  // Puntero a posición de pelota
  Vector2* ballVelocityPtr;

 public:
  /**
   * @brief Carga la textura del bot y lo pone en su posición original
   */
  void initializeBot(Ball* ball);

  /**
   * @brief dibuja textura del bot.
   */
  void drawBot();

  /**
   * @brief Mueve bot hacia arriba y abajo continuamente
   */
  void moveBot();

  /**
   * @brief Restablece posición de bot en el mapa
   */
  void resetBot();

  /**
   * @brief hitbox del bot
   */
  HitBox_t getRectangle();
};
