// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "button.h"
#include "label.h"
#include "shared.h"

/**
 * @brief Clase que representa la pantalla de bienvenida del juego
 */
class Home {
 private:
  // Ruta al asset que representa el botón de inicio
  const char* start_button_path = "assets/homeScreen/start_button.png";
  const char* settings_button_path = "assets/homeScreen/settings_button.png";
  const char* logoPath = "assets/homeScreen/game_logo.png";
  const char* bg_paht = "assets/homeScreen/home_background.png";

  Vector2 logoPos = {
    .x = WINDOW_WIDTH/2.0f,
    .y = WINDOW_HEIGHT/4.0f
  };

  Button start_button;  // Botón de inicio
  Button settings_button;
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
   * @brief Para ir a settings
   */
  void gameSettings(byte& settings, SoundManager* soundManager);

  /**
   * @brief Verifica si se dio click al botón de inicio
   */
  void hasGameStarted(byte&, SoundManager* soundManager);
};
