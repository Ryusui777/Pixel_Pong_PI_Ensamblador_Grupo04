// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Home.h"

void Home::initializeHomeScreen() {
  // Se inicializa el botón que tenemos en la pantalla de bienvenida
  this->start_button.init((char*)start_button_path, startPos);
}


void Home::drawHomeScreen() {
  // Se dibuja botón que permite iniciar partida
  this->start_button.draw();
}

void Home::hasGameStarted(byte& startVar) {
  // True si se le dio click al botón
  startVar = (this->start_button.isClicked()) ? 1 : startVar;
  // True si se tocó enter
  if (IsKeyDown(KEY_ENTER)) startVar = 1;
}
