// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include <stdio.h>
#include "Window.h"
#include "Game.h"
#include "Menu.h"
#include "Home.h"

int main() {
  // Componentes del juego
  Window window;
  Game Game;
  Home Home;
  Menu menu;

  // Inicialización de componentes
  window.initializeWindow();
  Home.initializeHomeScreen();
  Game.initializeGame();
  menu.initializeMenu();

  // Ciclo del juego
  std::uint8_t paused = 0;
  std::uint8_t inHome = 1;
  std::uint8_t ended = 0;
  std::uint8_t inGame = 0;

  while (!WindowShouldClose()) {
    window.beginWindowDraw();
    // Todo el resto de componentes se renderizan en este periodo
    if (inHome) {  // Pantalla de bienvenida
      Home.drawHomeScreen();
      Home.hasGameStarted(inGame);
      inHome = !(inGame);
      if (inGame) Game.resetMatch();  // Se reinicia el estado de juego
    } else if (inGame) {  // En partida
      Game.setInteractable();
      Game.drawGameElements();
      Game.isGamePaused(paused);
      inGame = !(paused);
      if (!inGame) Game.setNotInteractable();
    } else if (paused) {  // Partida pausada
      Game.drawGameElements();
      menu.drawMenu();
      menu.gameResumed(inGame);
      menu.goHome(inHome);
      paused = !(inGame);
      if (paused) paused = !(inHome);
    }
    // Terminar de mostrar un frame
    window.endWindowDraw();
  }
  window.killWindow();  // Se cierra la ventana (se presiona `esc`)
  return 0;
}
