// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "raylib.h"
#include "shared.h"
#include <stdio.h>

#define PLAYER_SPEED 8
#define PLAYER_ASSET_PATH (char*)"res/mainGame/red_player.png"

/** 
 * @brief Clase que representa al jugador humano de la partida
 */
class Player {
 private:
  Vector2 position;  // Posicion del jugador
  Texture2D texture;  // Textura del jugador
  void movePlayerDown();
  void movePlayerUp();

 public:
  /**
  * @brief Inicializa el jugador, carga su textura, y
  * posicion inicial. Esta debe ser llamada despues de
  * inicializar la pantalla de otra manera habra un error.
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

  void resetPlayerPosition();
};
