// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "settings.h"
#include "shared.h"

// Variables para posicionamiento de sliders
float ancho_barra = 10.0f;
float largo_barra = 300.0f;

Vector2 speedSliderPos = {
  ( WINDOW_WIDTH/ 2.0f)-largo_barra/2.0f,
  (WINDOW_HEIGHT/2.0f) - 10* ancho_barra 
};

Vector2 volumeSliderPos = {
  (WINDOW_WIDTH/2.0f) - largo_barra/2.0f,
  (WINDOW_HEIGHT/2.0f) + 10*ancho_barra/2.0f
};

void Settings::initializeSettings() {
  this->blurred_background = LoadTexture(bg_path);
  this->home_button.initializeButton((char*)home_button_path, (Vector2){9.0f*SCALE, 8.0f*SCALE});

  // Inicializar selector de velocidad

  speedSlider.initializeSlider(speedSliderPos, largo_barra, ancho_barra, 1.0f, 10.0f
    , 1.0f);
  ballSpeed = 10.0f;

  // Inicializar selector de volumen
  volumeSlider.initializeSlider(volumeSliderPos, largo_barra, ancho_barra, 1.0f, 10.0f
    , 3.0f);
}

void Settings::drawSettings(SoundManager* soundManager) {
  // Tapar logo, etc..
  Color c = {20, 7, 110, 255};
  DrawRectangle(0, 0, 1280, 720, c);

  // título del selector de velocidadd
  const char* speedTitle = "BALL SPEED";
  int speedTitleWidth = MeasureText(speedTitle, 30);
  DrawText(speedTitle, WINDOW_WIDTH / 2 - speedTitleWidth / 2, speedSliderPos.y - 60, 30
    , WHITE);

  // Actualizar el selector de velocidad
  speedSlider.updateSlider();
  // Dibujar el selector de velocidad
  speedSlider.drawSlider();

  // Actualizar la velocidad actual
  ballSpeed = speedSlider.getValue()+10.0f;

  const char* volumeTitle = "VOLUME";
  int volumeTitleWidth = MeasureText(volumeTitle, 30);
  DrawText(volumeTitle, WINDOW_WIDTH / 2 - volumeTitleWidth / 2, volumeSliderPos.y - 60, 30
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

  //TODO: Urgente cambiar esto 
  // Interfaz de usuario (botón de home)
  this->home_button.drawButton();
}

void Settings::goHome(byte& goHomeVar, SoundManager* soundManager) {
  goHomeVar = (this->home_button.isButtonBeingClicked(soundManager))
    ? 1 : goHomeVar;
}
