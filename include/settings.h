// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "shared.h"
#include "button.h"
#include "slider.h"

/**
 * @brief Clase encargada de los ajustes del juego
 */
class Settings {
 private:
  // Ruta al fondo del menú de settings (fondo azul con transparencia)
  const char* bg_path = "assets/settings/settings_background.png";

  // Ruta a botón de home
  const char* home_button_path ="assets/settings/home_button.png";

  // Fondo con blur
  Texture2D blurred_background;

  // Botón de regresar a home
  Button home_button;

  // Selector para controlar la velocidad de la bola
  Slider speedSlider;

  // Selector para controlar la velocidad de la bola
  Slider volumeSlider;

  // Velocidad actual de la pelota
  float ballSpeed;

 public:
  /**
   * @brief Inicializa los elementos de la clase, carga sus texturas y
   * posiciones.
   */
  void initializeSettings();

  /**
   * @brief Rederiza el menú en pantalla
   */
  void drawSettings(SoundManager* soundManager);

  /**
   * @brief Se regresa al inicio
   */
  void goHome(byte&, SoundManager* soundManager);

  /**
   * @brief Obtiene la velocidad actual configurada
   * @return Velocidad de la bola
   */
  float getBallSpeed() const {
    return ballSpeed;
  }
};
