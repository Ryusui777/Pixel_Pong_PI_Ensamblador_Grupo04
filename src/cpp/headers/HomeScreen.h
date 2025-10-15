// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "Button.h"
#include "Label.h"
#include "shared.h"

/**
 * @brief Clase que representa la pantalla de bienvenida del juego
 */
class Home {
 private:
  // Ruta al asset que representa el botón de inicio
  const char* start_button_path = "res/homeScreen/start.png";
    const char* logoPath="res/homeScreen/Logo.png";
  const char* bg_paht="res/homeScreen/bg.png";

  Vector2 logoPos= {
      .x = WINDOW_WIDTH/2.0f,
      .y = WINDOW_HEIGHT/4.0f
  };

  Button start_button;  // Botón de inicio
  Label logo;
  Texture2D blurBG;

 public:
  /**
   * @brief Inicializar pantalla de inicio
   */
  void initializeHomeScreen();

  /**
   * @brief Renderizar pantalla de bienvenida
   */
  void drawHomeScreen();

  /**
   * @brief Verifica si se dio click al botón de inicio
   */
  void hasGameStarted(byte&);
};
