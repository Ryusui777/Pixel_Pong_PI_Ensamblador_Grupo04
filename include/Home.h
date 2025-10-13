// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "Button.h"
#include "shared.h"

/**
 * @brief Clase que representa la pantalla de bienvenida del juego
 */
class Home {
 private:
  // Ruta al asset que representa el botón de inicio
  const char* start_button_path = "assets/homeScreen/start_button.png";
  Button start_button;  // Botón de inicio
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
