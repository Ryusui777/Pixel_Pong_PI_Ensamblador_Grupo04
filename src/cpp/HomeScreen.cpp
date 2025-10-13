// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "HomeScreen.h"

void HomeScreen::init() {
  // Se inicializa el botón que tenemos en la pantalla de bienvenida
  this->start.init((char*)start_path, startPos);
}


void HomeScreen::draw() {
  // Se dibuja botón que permite iniciar partida
  this->start.draw();
}

void HomeScreen::started(byte& startVar) {
  // True si se le dio click al botón
  startVar = (this->start.isClicked()) ? 1 : startVar;
  // True si se tocó enter
  if (IsKeyDown(KEY_ENTER)) startVar = 1;
}
