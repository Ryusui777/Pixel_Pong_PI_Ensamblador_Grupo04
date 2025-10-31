// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Settings.h"

void Settings::initializeSettings() {
  this->blurred_background = LoadTexture(bg_path);
  this->home_button.initializeButton((char*)home_button_path, home_button_pos);

  // Inicializar selector de velocidad
  Vector2 speedSliderPos = {
    (1280 / 2.0f) - 150.0f,
    (720 / 4.0f) - 35.0f
  };
  speedSlider.initializeSlider(speedSliderPos, 300.0f, 10.0f, 10.0f, 20.0f
    , 10.0f);
  ballSpeed = 10.0f;

  // Inicializar selector de volumen
  Vector2 volumeSliderPos = {
    (1280 / 2.0f) - 150.0f,
    (720 / 4.0f) + 100.0f
  };
  volumeSlider.initializeSlider(volumeSliderPos, 300.0f, 10.0f, 0.0f, 1.0f
    , 0.5f);
}

void Settings::drawSettings(SoundManager* soundManager) {
  // Tapar logo, etc..
  DrawRectangle(0, 0, 1280, 720, (Color){20, 7, 110, 255});

  // título del selector de velocidadd
  const char* speedTitle = "VELOCIDAD DE LA BOLA";
  int speedTitleWidth = MeasureText(speedTitle, 30);
  DrawText(speedTitle, 1280 / 2 - speedTitleWidth / 2, 720 / 4 - 100, 30
    , WHITE);

  // Actualizar el selector de velocidad
  speedSlider.updateSlider();
  // Dibujar el selector de velocidad
  speedSlider.drawSlider();

  // Actualizar la velocidad actual
  ballSpeed = speedSlider.getValue();

  const char* volumeTitle = "VOLUMEN";
  int volumeTitleWidth = MeasureText(volumeTitle, 30);
  DrawText(volumeTitle, 1280 / 2 - volumeTitleWidth / 2, 720 / 4 + 20, 30
    , WHITE);

  // Actualizar el selector de sonido
  volumeSlider.updateSlider();
  // Dibujar el selector de sonido
  volumeSlider.drawSlider();

  // Subir o bajar sonido
  if (soundManager) {
    float currentVolume = volumeSlider.getValue();
    soundManager->setVolume(currentVolume);
  }

  // Interfaz de usuario (botón de home)
  this->home_button.drawButton();
}

void Settings::goHome(byte& goHomeVar, SoundManager* soundManager) {
  goHomeVar = (this->home_button.isButtonBeingClicked(soundManager))
    ? 1 : goHomeVar;
}
