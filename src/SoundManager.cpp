// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "SoundManager.h"
#include <stdio.h>

SoundManager::SoundManager() {}

SoundManager::~SoundManager() {
  unloadSounds();
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
}

void SoundManager::unloadSounds() {
  UnloadSound(buttonClickSound);
  UnloadSound(paddleSound);
  UnloadSound(paddleSound);
  UnloadSound(wallHitSound);
  UnloadSound(playerScoreSound);
  UnloadSound(botScoreSound);
  CloseAudioDevice();
}

void SoundManager::playButtonClick() {
  PlaySound(buttonClickSound);
}

void SoundManager::playPaddleHit() {
  PlaySound(paddleSound);
}

void SoundManager::playWallHit() {
  PlaySound(wallHitSound);
}

void SoundManager::playPlayerScore() {
  PlaySound(playerScoreSound);
}

void SoundManager::playBotScore() {
  PlaySound(botScoreSound);
}

void SoundManager::setVolume(float volume) {
  SetSoundVolume(buttonClickSound, volume);
  SetSoundVolume(paddleSound, volume);
  SetSoundVolume(paddleSound, volume);
  SetSoundVolume(wallHitSound, volume);
  SetSoundVolume(playerScoreSound, volume);
  SetSoundVolume(botScoreSound, volume);
}
