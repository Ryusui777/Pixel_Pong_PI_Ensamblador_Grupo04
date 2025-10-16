// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Home.h"
#include "Button.h"
void Home::initializeHomeScreen() {
  // Se inicializa el botón que tenemos en la pantalla de bienvenida
  this->blurBG = LoadTexture(bg_paht);
  this->start_button.initializeButton((char*)start_button_path
    , start_button_pos);
    this->logo.initializeLabel((char*)logoPath, logoPos);
}

void Home::drawHomeScreen() {
    // Background
    float drawW = blurBG.width * SCALE;
    float drawH = blurBG.height * SCALE;
    float offsetX = (WINDOW_WIDTH  - drawW) / 2.0f;
    float offsetY = (WINDOW_HEIGHT - drawH) / 2.0f;
    DrawTextureEx(blurBG, {offsetX, offsetY}, 0.0f, SCALE, WHITE);

    this->start_button.drawButton();
    this->logo.drawLabel();
}

void Home::hasGameStarted(byte& startVar) {
  // True si se le dio click al botón
  startVar = (this->start_button.isButtonBeingClicked()) ? 1 : startVar;
  // True si se tocó enter
  if (IsKeyDown(KEY_ENTER)) startVar = 1;
}
