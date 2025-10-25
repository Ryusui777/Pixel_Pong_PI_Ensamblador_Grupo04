// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include <stdio.h>
#include "Window.h"
#include "Game.h"
#include "Menu.h"
#include "Home.h"
#include "Settings.h"

int main() {
  // Componentes
  Window window;
  Game mainGame;
  Home homeScreen;
  Menu menu;
  Settings settings;

  // Inicializacion de componentes
  window.initializeWindow();
  homeScreen.initializeHomeScreen();
  mainGame.initializeGame();
  menu.initializeMenu();
  settings.initializeSettings();

  // Ciclo del juego
  std::uint8_t paused = 0;
  std::uint8_t inHome = 1;
  std::uint8_t inGame = 0;
  std::uint8_t inSettings = 0;

  while (!WindowShouldClose()) {
    window.beginWindowDraw();
    if (inHome) {
      homeScreen.drawHomeScreen();
      homeScreen.hasGameStarted(inGame);
      homeScreen.gameSettings(inSettings);
      inHome = !(inGame || inSettings);
      if (inGame) {
        // Aplica la velocidad configurada antes de empezar el juego
        mainGame.applyBallSpeed(settings.getBallSpeed());
        mainGame.resetMatch();  // resetea el estado de juego
      }
    } else if (inSettings) {  // ajustes en pantalla de bienvenida
      homeScreen.drawHomeScreen();
      settings.drawSettings();
      settings.goHome(inHome);
      inSettings = !(inHome);
    } else if (inGame) {  // partida
      mainGame.setInteractable();
      mainGame.drawGameElements();
      mainGame.isGamePaused(paused);
      inGame = !(paused);
      if (!inGame) mainGame.setNotInteractable();
    } else if (paused) {  // menú de pausa dentro del juego
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
