// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "SoundManager.h"
#include "shared.h"

extern "C" int  isBallOpossingPlayer();
extern "C" void setBallSpeed(float newSpeed);
extern "C" void initPelotaMovement(Vector2*, Vector2*, float, float);
extern "C" void pelotaReverseY();
extern "C" void pelotaReverseX();
extern "C" void pelotaMove();
extern "C" void resetBall();
extern "C" void pelotaReboto();

/**
 * @brief Clase que representa la pelota del juego
 */
class Ball {
 private:
  // Ruta a la imagen de la bola
  const char* ball_path = "assets/mainGame/ball.png";
  Texture2D texture;  // Textura de la bola
  Vector2 position;  // Posición de la bola
  Vector2 velocity;  // Velocidad de la bola
  float speed;

 public:
  friend class Bot;
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
  void moveBall(SoundManager* soundManager);

  /**
   * @brief Restablece posición de la bola
   */
  void resetBallPosition();

  /* Manejo de colisiones */

  /**
   * @brief Manejo de choques con paredes
   */
  void checkBoundaryCollision(SoundManager* soundManager);

  /**
   * @brief Invertir trayectoria sobre eje X
   */
  void reverseHorizontalTrajectory();

  /**
   * @brief Invertir trayectoria sobre eje Y
   */
  void reverseVerticalTrajectory();

  /**
   * @brief manejo de rebote contra jugador
   */
  void rebotarContraJugador(SoundManager* soundManager);

  /**
   * @brief manejo de rebote contra bot
   */
  void rebotarContraBot(SoundManager* soundManager);

  /**
   * @brief Método encargado de establecer la velocidad de la bola
   * @param speed Valor entre 10 y 20
   */
  void setSpeed(float speed) {
    setBallSpeed(speed);
  }

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
