// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include <stdio.h>
#include "Window.h"
#include "Game.h"
#include "Menu.h"
#include "Home.h"
#include "Settings.h"
#include "SoundManager.h"

int main() {
  // Componentes
  Window window;
  Game mainGame;
  Home homeScreen;
  Menu menu;
  Settings settings;
  SoundManager soundManager;

  // Inicializacion de componentes
  window.initializeWindow();
  soundManager.initializeSounds();
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
      homeScreen.hasGameStarted(inGame, &soundManager);
      homeScreen.gameSettings(inSettings, &soundManager);
      inHome = !(inGame || inSettings);
      if (inGame) {
        // Aplica la velocidad configurada antes de empezar el juego
        mainGame.applyBallSpeed(settings.getBallSpeed());
        mainGame.resetMatch();  // resetea el estado de juego
      }
    } else if (inSettings) {  // ajustes en pantalla de bienvenida
      homeScreen.drawHomeScreen();
      settings.drawSettings(&soundManager);
      settings.goHome(inHome, &soundManager);
      inSettings = !(inHome);
    } else if (inGame) {  // partida
      mainGame.setInteractable();
      mainGame.drawGameElements(&soundManager);
      mainGame.isGamePaused(paused, &soundManager);
      inGame = !(paused);
      if (!inGame) mainGame.setNotInteractable();
    } else if (paused) {  // menú de pausa dentro del juego
      mainGame.drawGameElements(&soundManager);
      menu.drawMenu();
      menu.gameResumed(inGame, &soundManager);
      menu.goHome(inHome, &soundManager);
      paused = !(inGame);
      if (paused) paused = !(inHome);
    }
    window.endWindowDraw();
  }

  soundManager.unloadSounds();
  window.killWindow();  // Cierra la ventana
  return 0;
}
