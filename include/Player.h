// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "raylib.h"
<<<<<<< HEAD
#include "arduinoController.h"
=======
#include "arduino_controller.h"
>>>>>>> 5f6bb0d (Se agregan archivos para uso de joystick)
#include "shared.h"
#include <stdio.h>

#define PLAYER_SPEED 8
#define PLAYER_ASSET_PATH (char*)"assets/mainGame/player_red.png"

/** 
 * @brief Clase que representa al jugador humano de la partida
 */
class Player {
 private:
  Vector2 position;  // Posicion del jugador
  Texture2D texture;  // Textura del jugador
  ArduinoController arduino;

  /**
   * @brief Auxiliar de `movePlayer()` para mover hacia arriba al jugador
   */
  void movePlayerDown();

  /**
   * @brief Auxiliar de `movePlayer()` para mover hacia abajo al jugador
   */
  void movePlayerUp();

 public:
  /**
  * @brief Inicializa al jugador, carga su textura, y posicion inicial. 
  * @remark Debe ser llamada despues de inicializar la pantalla. De otra manera,
  * habrá un error.
  */
  void initializePlayer();

  /**
  * @brief Renderiza el jugador en pantalla
  */
  void drawPlayer();

  /**
   * @brief Se mueve al jugador hacia arriba o abajo según input de teclado
   */
  void movePlayer();

  /**
   * @brief Se restablece posición de jugador dentro del mapa de juego.
   */
  void resetPlayerPosition();

  /**
   * @brief Rectangulo del jugador
  */
  Rectangle getRectangle();
};
