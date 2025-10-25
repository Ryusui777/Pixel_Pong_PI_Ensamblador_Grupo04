// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "shared.h"
#include "Button.h"

/**
 * @brief Clase encargada de los ajustes del juego
 */
class Settings {
 private:
  // Ruta al fondo del menú de settings (fondo azul con transparencia)
  const char* bg_path = "assets/settings/settings_background.png";
  // // Ruta a botón de resume
  // const char* resume_button_path ="assets/menu/resume_button.png";
  // Ruta a botón de home
  const char* home_button_path ="assets/settings/home_button.png";

  // Fondo con blur
  Texture2D blurred_background;
  // // Botón de regresar a partida
  // Button resume_button;
  // Botón de regresar a home
  Button home_button;

 public:
  /**
   * @brief Inicializa los elementos de la clase, carga sus texturas y
   * posiciones.
   */
  void initializeSettings();

  /**
   * @brief Rederiza el menú en pantalla
   */
  void drawSettings();

  // /**
  //  * @brief Se regresa a la partida
  //  */
  // void homeResumed(byte&);

  /**
   * @brief Se regresa al inicio
   */
  void goHome(byte&);
};
