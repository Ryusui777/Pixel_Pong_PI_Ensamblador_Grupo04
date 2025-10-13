// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Menu.h"

void Menu::initializeMenu() {
  this->blurred_background = LoadTexture(bg_path);
  this->home_button.init((char*)home_button_path, homePos);
  this->resume_button.init((char*)resume_button_path, resumePos);
}

void Menu::drawMenu() {
  // Background
  float drawW = blurred_background.width * SCALE;
  float drawH = blurred_background.height * SCALE;
  float offsetX = (WINDOW_WIDTH  - drawW) / 2.0f;
  float offsetY = (WINDOW_HEIGHT - drawH) / 2.0f;
  DrawTextureEx(blurred_background, {offsetX, offsetY}, 0.0f, SCALE, WHITE);

  // UI elements
  this->home_button.draw();
  this->resume_button.draw();
}

void Menu::gameResumed(byte& resumeVar) {
  resumeVar = (this->resume_button.isClicked())? 1 : resumeVar;
}

void Menu::goHome(byte& goHomeVar) {
  goHomeVar = (this->home_button.isClicked())? 1 : goHomeVar;
}
