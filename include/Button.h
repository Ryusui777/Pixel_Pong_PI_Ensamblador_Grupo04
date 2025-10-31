// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include <stdio.h>
#include "shared.h"
#include "raylib.h"

const Vector2 home_button_pos = {
  .x = WINDOW_WIDTH/2.0f,
  .y = WINDOW_HEIGHT/2.0f + 60
};

const Vector2 resume_button_pos = {
  .x = WINDOW_WIDTH/2.0f,
  .y = WINDOW_HEIGHT/2.0f - 60
};

const Vector2 pause_button_pos = {
  .x = WINDOW_WIDTH/2.0f,
  .y = 25.0f
};

const Vector2 start_button_pos = {
  .x = WINDOW_WIDTH/2.0f,
  .y = WINDOW_HEIGHT/2.0f + 60
};

const Vector2 settings_button_pos = {
  .x = WINDOW_WIDTH/2.0f,
  .y = WINDOW_HEIGHT/2.0f + 200
};

/**
 * @brief Maneja la posición de los botones
 */
class Button {
 private:
  Vector2 position;  // Posicion del botón
  Texture2D texture;  // textura del botón

 public:
  /**
   * @brief Constructor
   */
  Button();

  /**
   * @brief Carga la textura de un botón y su posición inicial
   */
  void initializeButton(char*, Vector2);

  /**
   * @brief Dibuja un botón en pantalla
   */
  void drawButton();

  /**
   * @brief Determina si el mouse se encuentra en el área del botón
   * @return 1 si el mouse está en el área del botón, 0 si no
  */
  byte isMouseAboveButton();

  /**
   * @brief  Determina si el botón está siendo presionado, si ya fue presionado
   * y el usuario mantiene presionado solo se activa una vez
   * @return 1 si fue presionado, 0 si no
   */
  byte isButtonBeingClicked() {
    return isMouseAboveButton() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
  }
};
