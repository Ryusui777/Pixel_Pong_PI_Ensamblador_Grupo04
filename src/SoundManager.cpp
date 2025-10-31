// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "SoundManager.h"
#include <stdio.h>

SoundManager::SoundManager()
  : masterVolume(0.5f)
  , initialized(false) {
  }

SoundManager::~SoundManager() {
  if (initialized) {
    unloadSounds();
  }
}

void SoundManager::initializeSounds() {
  // Inicializar audio
  InitAudioDevice();

  // Cargar archivos de sonido
  buttonClickSound = LoadSound("assets/sound/clickButton.wav");
  paddleSound = LoadSound("assets/sound/impactPaddle.wav");
  paddleSound = LoadSound("assets/sound/impactPaddle.wav");
  wallHitSound = LoadSound("assets/sound/impactWall.wav");
  playerScoreSound = LoadSound("assets/sound/botScores.wav");
  botScoreSound = LoadSound("assets/sound/playerScores.wav");

  // Nivel de volumen inicial
  SetSoundVolume(buttonClickSound, masterVolume);
  SetSoundVolume(paddleSound, masterVolume);
  SetSoundVolume(paddleSound, masterVolume);
  SetSoundVolume(wallHitSound, masterVolume);
  SetSoundVolume(playerScoreSound, masterVolume);
  SetSoundVolume(botScoreSound, masterVolume);
  initialized = true;
}

void SoundManager::unloadSounds() {
  if (!initialized) return;

  UnloadSound(buttonClickSound);
  UnloadSound(paddleSound);
  UnloadSound(paddleSound);
  UnloadSound(wallHitSound);
  UnloadSound(playerScoreSound);
  UnloadSound(botScoreSound);

  CloseAudioDevice();
  initialized = false;
}

void SoundManager::playButtonClick() {
  if (initialized) {
    PlaySound(buttonClickSound);
  }
}

void SoundManager::playPaddleHit() {
  if (initialized) {
    PlaySound(paddleSound);
  }
}

void SoundManager::playWallHit() {
  if (initialized) {
    PlaySound(wallHitSound);
  }
}

void SoundManager::playPlayerScore() {
  if (initialized) {
    PlaySound(playerScoreSound);
  }
}

void SoundManager::playBotScore() {
  if (initialized) {
    PlaySound(botScoreSound);
  }
}

// Esto debe cambiar; ir en ensamblador
// Este metodo está hecho con IA
void SoundManager::setVolume(float volume) {
  if (volume < 0.0f) volume = 0.0f;
  if (volume > 1.0f) volume = 1.0f;

  masterVolume = volume;

  if (initialized) {
    SetSoundVolume(buttonClickSound, masterVolume);
    SetSoundVolume(paddleSound, masterVolume);
    SetSoundVolume(paddleSound, masterVolume);
    SetSoundVolume(wallHitSound, masterVolume);
    SetSoundVolume(playerScoreSound, masterVolume);
    SetSoundVolume(botScoreSound, masterVolume);
  }
}

float SoundManager::getVolume() const {
  return masterVolume;
}
