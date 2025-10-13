// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include <stdio.h>
#include "Window.h"
#include "Game.h"
#include "Menu.h"
#include "Home.h"

int main() {
  // Componentes del juego
  Window window;
  Game game;
  Home home;
  Menu menu;

  // Inicialización de componentes
  window.initializeWindow();
  home.initializeHomeScreen();
  game.initializeGame();
  menu.initializeMenu();

  // Ciclo del juego
  std::uint8_t paused = 0;
  std::uint8_t atHome = 1;
  // std::uint8_t ended = 0;
  std::uint8_t playing = 0;

  while (!WindowShouldClose()) {
    window.beginWindowDraw();
    // Todo el resto de componentes se renderizan en este periodo
    if (atHome) {  // Pantalla de bienvenida
      home.drawHomeScreen();
      home.hasGameStarted(playing);
      atHome = !(playing);
      if (playing) game.resetMatch();  // Se reinicia el estado de juego
    } else if (playing) {  // En partida
      game.setInteractable();
      game.drawGameElements();
      game.isGamePaused(paused);
      playing = !(paused);
      if (!playing) game.setNotInteractable();
    } else if (paused) {  // Partida pausada
      game.drawGameElements();
      menu.drawMenu();
      menu.gameResumed(playing);
      menu.goHome(atHome);
      paused = !(playing);
      if (paused) paused = !(atHome);
    }
    // Terminar de mostrar un frame
    window.endWindowDraw();
  }
  window.killWindow();  // Se cierra la ventana (se presiona `esc`)
  return 0;
}
