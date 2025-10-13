// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include <stdio.h>
#include "Window.h"
#include "MainGame.h"
#include "Menu.h"
#include "HomeScreen.h"

int main() {
  // Componentes del juego
  Window window;
  MainGame mainGame;
  HomeScreen homeScreen;
  Menu menu;

  // Inicialización de componentes
  window.initializeWindow();
  homeScreen.init();
  mainGame.init();
  menu.init();

  // Ciclo del juego
  std::uint8_t paused = 0;
  std::uint8_t inHome = 1;
  std::uint8_t ended = 0;
  std::uint8_t inGame = 0;

  while (!WindowShouldClose()) {
    window.beginWindowDraw();
    // Todo el resto de componentes se renderizan en este periodo
    if (inHome) {  // Pantalla de bienvenida
      homeScreen.draw();
      homeScreen.started(inGame);
      inHome = !(inGame);
      if (inGame) mainGame.reset();  // Se reinicia el estado de juego
    } else if (inGame) {  // En partida
      mainGame.setInteractable();
      mainGame.draw();
      mainGame.isPaused(paused);
      inGame = !(paused);
      if (!inGame) mainGame.setNotInteractable();
    } else if (paused) {  // Partida pausada
      mainGame.draw();
      menu.draw();
      menu.resumed(inGame);
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
