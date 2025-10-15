// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Window.h"

void Window::initializeWindow() {
  // Inicializa la ventana
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pixel pong");

  // Carga la textura del game_background
  this->game_background = LoadTexture(game_background_path);

  // Establece los FPS
  SetTargetFPS(60);
}


void Window::beginWindowDraw() {
  BeginDrawing();
  drawWindowBackground();
}

void Window::endWindowDraw() {
  EndDrawing();
}

void Window::drawWindowBackground() {
  float drawW = game_background.width * SCALE;
  float drawH = game_background.height * SCALE;
  float offsetX = (WINDOW_WIDTH  - drawW) / 2.0f;
  float offsetY = (WINDOW_HEIGHT - drawH) / 2.0f;
  DrawTextureEx(game_background, {offsetX, offsetY}, 0.0f, SCALE, WHITE);
}
