// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "raylib.h"

/**
 * @brief clase que maneja el sonido
 */
class SoundManager {
 private:
  // Sonido de click a botón
  Sound buttonClickSound;
  // Sonido cuando bola toca raqueta
  Sound paddleSound;
  // Sonido cuando bola golpea pared
  Sound wallHitSound;
  // Sonido cuando se anota un punto al jugador
  Sound playerScoreSound;
  // Sonido cuando se anota un punto al bot
  Sound botScoreSound;

 public:
  SoundManager();
  ~SoundManager();

  /**
   * @brief Inicializar sonidos
   */
  void initializeSounds();

  /**
   * @brief Desicinializar sonidos
   */
  void unloadSounds();

  /**
   * @brief Hacer sonido de click al presionar un botón
   */
  void playButtonClick();

  /**
   * @brief Hacer sonido de golpe cuando bola toca paleta
   */
  void playPaddleHit();

  /**
   * @brief Hacer sonido de rebote cuando bola toca paleta
   */
  void playWallHit();

  /**
   * @brief Hacer sonido cuando se anota puntos a jugador
  */
  void playPlayerScore();

  /**
   * @brief Hacer sonido cuando se anota puntos a bot
  */
  void playBotScore();

  /**
   * @brief establecer volumen
   */
  void setVolume(float volume);
};
