// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Settings.h"

void Settings::initializeSettings() {
  this->blurred_background = LoadTexture(bg_path);
  this->home_button.initializeButton((char*)home_button_path, home_button_pos);
  // this->resume_button.initializeButton((char*)resume_button_path
  //   , resume_button_pos);
}

void Settings::drawSettings() {
  // Fondo
  float drawW = blurred_background.width * SCALE;
  float drawH = blurred_background.height * SCALE;
  float offsetX = (WINDOW_WIDTH  - drawW) / 2.0f;
  float offsetY = (WINDOW_HEIGHT - drawH) / 2.0f;
  DrawTextureEx(blurred_background, {offsetX, offsetY}, 0.0f, SCALE, WHITE);

  // Interfaz de usuario
  this->home_button.drawButton();
  // this->resume_button.drawButton();
}

// void Settings::gameResumed(byte& resumeVar) {
//   resumeVar = (this->resume_button.isButtonBeingClicked())? 1 : resumeVar;
// }

void Settings::goHome(byte& goHomeVar) {
  goHomeVar = (this->home_button.isButtonBeingClicked())? 1 : goHomeVar;
}
