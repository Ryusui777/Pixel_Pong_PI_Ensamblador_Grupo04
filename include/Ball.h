// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "shared.h"

extern "C" int  isBallOpossingPlayer();

/**
 * @brief Clase que representa la pelota del juego
 */
class Ball {
 private:
  // Ruta a la imagen de la bola
  const char* ball_path = "assets/mainGame/ball.png";
  Texture2D texture;  // Textura de la bola
  Vector2 position;  // Posición de la bola
  Vector2 velocity;  // Velocidad de la bola ???
  float speed;

 public:
  /**
   * @brief Se inicializa la bola
   */
  void initializeBall();

  /**
   * @brief Renderiza la bola
   */
  void drawBall();

  /**
   * @brief Maneja movimiento de la bola
   */
  void moveBall();

  /**
   * @brief Restablece posición de la bola
   */
  void resetBallPosition();

  /* Manejo de colisiones */

  /**
   * @brief Manejo de choques con paredes
   */
  void checkBoundaryCollision();

  /**
   * @brief Invertir trayectoria sobre eje X
   */
  void reverseHorizontalTrajectory();

  /**
   * @brief Invertir trayectoria sobre eje Y
   */
  void reverseVerticalTrajectory();

  void rebotarContraJugador();
  void rebotarContraBot();
  /* Getters para la posición y tamaño (necesarios para colisiones) */

  /**
   * @brief Getter para posición de la bola
   */
  Vector2 getBallPosition() const { return position; }

  /**
   * @brief Getter para ancho de pelota
   */
  float getBallWidth() const { return texture.width * SCALE; }

  /**
   * @brief Getter para altura de pelota
   */
  float getBallHeight() const { return texture.height * SCALE; }

  /**
   * @brief Getter para hitbox de pelota (?????)
   */
  Rectangle getRect() const {
    return {position.x - getBallWidth()/2, position.y
      - getBallHeight()/2, getBallWidth(), getBallHeight()};
  }

  /**
   * @brief Verifica si la bola va hacia el jugador
   */
  int isOpposing() {
    return isBallOpossingPlayer();
  }
};
