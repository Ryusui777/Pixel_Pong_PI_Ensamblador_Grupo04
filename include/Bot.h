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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  Vector2* ballPositionPtr = nullptr;
  Vector2* ballVelocityPtr = nullptr;
=======
  Vector2* ballPositionPtr;  // Puntero a posición de pelota
  Vector2* ballVelocityPtr;
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
=======
  Vector2* ballPositionPtr = nullptr;
  Vector2* ballVelocityPtr = nullptr;
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
=======
  Vector2* ballPositionPtr;  // Puntero a posición de pelota
  Vector2* ballVelocityPtr;
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
=======
  Vector2* ballPositionPtr = nullptr;
  Vector2* ballVelocityPtr = nullptr;
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)

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
  Rectangle getRectangle();
};
