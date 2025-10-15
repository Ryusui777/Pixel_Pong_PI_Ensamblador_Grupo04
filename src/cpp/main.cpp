// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include <stdio.h>
#include "Window.h"
#include "MainGame.h"
#include "Menu.h"
#include "HomeScreen.h"

int main() {
  // Componentes
  Window window;
  Game mainGame;
  Home homeScreen;
  Menu menu;

  // Inicializacion de componentes
  window.initializeWindow();
  homeScreen.initializeHomeScreen();
  mainGame.initializeGame();
  menu.initializeMenu();

  // Ciclo del juego
  std::uint8_t paused = 0;
  std::uint8_t inHome = 1;
  std::uint8_t ended = 0;
  std::uint8_t inGame = 0;

  while (!WindowShouldClose()) {
    window.beginWindowDraw();
    // Todo el resto de componentes se renderizan en este periodo
    if (inHome) {
      homeScreen.drawHomeScreen();
      homeScreen.hasGameStarted(inGame);
      inHome = !(inGame);
      if (inGame) mainGame.resetMatch();  // resetea el juego
    } else if (inGame) {
      mainGame.setInteractable();
      mainGame.drawGameElements();
      mainGame.isGamePaused(paused);
      inGame = !(paused);
      if (!inGame) mainGame.setNotInteractable();
    } else if (paused) {
      mainGame.drawGameElements();
      menu.drawMenu();
      menu.gameResumed(inGame);
      menu.goHome(inHome);
      paused = !(inGame);
      if (paused) paused = !(inHome);
    }
    window.endWindowDraw();
  }
  window.killWindow();  // Cierra la vantana
  return 0;
}
