// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Settings.h"

void Settings::initializeSettings() {
  this->blurred_background = LoadTexture(bg_path);
  this->home_button.initializeButton((char*)home_button_path, home_button_pos);

  // Inicializar selector de velocidad
  Vector2 sliderPos = {
    (1280 / 2.0f) - 150.0f,
    (720 / 4.0f) - 35.0f
  };
  speedSlider.initializeSlider(sliderPos, 300.0f, 10.0f, 10.0f, 20.0f, 10.0f);
  ballSpeed = 10.0f;
}

void Settings::drawSettings() {
  // Tapar logo, etc..
  DrawRectangle(0, 0, 1280, 720, (Color){20, 7, 110, 255});

  const char* title = "VELOCIDAD DE LA BOLA"; // título del selector
  int titleWidth = MeasureText(title, 30);
  DrawText(title, 1280 / 2 - titleWidth / 2, 720 / 4 - 100, 30, WHITE);

  // Actualizar el selector
  speedSlider.updateSlider();
  // Dibujar el selector
  speedSlider.drawSlider();
  
  // Actualizar la velocidad actual
  ballSpeed = speedSlider.getValue();

  // Interfaz de usuario (botón de home)
  this->home_button.drawButton();
}

void Settings::goHome(byte& goHomeVar) {
  goHomeVar = (this->home_button.isButtonBeingClicked())? 1 : goHomeVar;
}
