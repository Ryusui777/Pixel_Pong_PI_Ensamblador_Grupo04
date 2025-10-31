// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "shared.h"
#include "Button.h"

/**
 * @brief Clase encargada del manejo del menú de juego
 */
class Menu {
 private:
  // Ruta al fondo del menú (fondo azul con transparencia)
  const char* bg_path = "assets/menu/menu_background.png";
  // Ruta a botón de resume
  const char* resume_button_path ="assets/menu/resume_button.png";
  // Ruta a botón de home
  const char* home_button_path ="assets/menu/home_button.png";

  // Fondo con blur
  Texture2D blurred_background;
  // Botón de regresar a partida
  Button resume_button;
  // Botón de regresar a home
  Button home_button;

 public:
  /**
   * @brief Inicializa los elementos de la clase, carga sus texturas y
   * posiciones.
   */
  void initializeMenu();

  /**
   * @brief Rederiza el menú en pantalla
   */
  void drawMenu();

  /**
   * @brief Se regresa a la partida
   */
  void gameResumed(byte&, SoundManager* soundManager);

  /**
   * @brief Se regresa al inicio
   */
  void goHome(byte&, SoundManager* soundManager);
};
