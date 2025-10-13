// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "shared.h"
#include "Player.h"
#include "Button.h"
#include "Bot.h"
#include "Ball.h"

/**
 * @brief Clase responsable de la partida en juego.
 */
class Game {
 private:
  // Path al botón de pausa
  const char* pause_button_path = "res/mainGame/pause_button.png";
  // Objeto jugador humano
  Player player;
  // Objeto jugador no humano
  Bot bot;
  // Pelota
  Ball ball;
  // Botón de pausa en la parte superior de la pantalla de la partida
  Button pause_button;
  // Indicador de si un elemento es interactuable
  std::uint8_t interactable;

  void updateElements();

 public:
  /**
   * @brief Inicializa los elementos de la clase,
   * carga sus texturas y posiciones.
   */
  void initializeGame();

  /**
   * @brief Rederiza los elementos de la partida en pantalla.
   */
  void drawGameElements();

  /**
   * @brief Cambia el estado del juego,
   * si la varible que cambia esta en 0
   * entonces los componentes se vuelven
   * no interactuales.
   */
  void setInteractable() {
    interactable = 1;
  }

  void setNotInteractable() {
    interactable = 0;
  }

  /**
   * @brief Método encargado de verificar si la partida se encuentra pausada.
   * @remarks La partida se pausa tocando el botón de pausa en la ventana o con
   * la tecla espacio.
   */
  void isGamePaused(byte&);

  /**
   * @brief Restablece el progreso de la partida.
   */
  void resetMatch();
};
