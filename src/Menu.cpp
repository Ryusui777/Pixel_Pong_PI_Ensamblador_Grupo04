// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Menu.h"

void Menu::initializeMenu() {
  this->blurred_background = LoadTexture(bg_path);
  this->home_button.initializeButton((char*)home_button_path, home_button_pos);
  this->resume_button.initializeButton((char*)resume_button_path
    , resume_button_pos);
}

void Menu::drawMenu() {
  // Fondo
  float drawW = blurred_background.width * SCALE;
  float drawH = blurred_background.height * SCALE;
  float offsetX = (WINDOW_WIDTH  - drawW) / 2.0f;
  float offsetY = (WINDOW_HEIGHT - drawH) / 2.0f;
  DrawTextureEx(blurred_background, {offsetX, offsetY}, 0.0f, SCALE, WHITE);

  // Interfaz de usuario
  this->home_button.drawButton();
  this->resume_button.drawButton();
}

void Menu::gameResumed(byte& resumeVar, SoundManager* soundManager) {
  resumeVar = (this->resume_button.isButtonBeingClicked(soundManager))? 1
    : resumeVar;
}

void Menu::goHome(byte& goHomeVar, SoundManager* soundManager) {
  goHomeVar = (this->home_button.isButtonBeingClicked(soundManager))? 1
    : goHomeVar;
}
