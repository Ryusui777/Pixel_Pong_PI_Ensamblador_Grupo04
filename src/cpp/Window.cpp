// #include "Window.h"

// #include "Window.h"

// void Window::init(){

//     // Dimesiones de la ventana
//     this->width = WIDTH;
//     this->height = HEIGHT;

//     // Inicializa la ventana
// 	InitWindow(width, height, "Pixel pong");

//     // Carga la textura del bg
//     bg = LoadTexture(bg_path);

//     // Establece la velocidad de refrescamiento
//     SetTargetFPS(60);
// }


// void Window::beginDraw(){
//         BeginDrawing();
//             drawBG();
// }

// void Window::draw(Texture2D texture, Vector2 pos){
//     DrawTexture(texture, pos.x, pos.y, BLACK);
// }

// void Window::endDraw(){
//     EndDrawing();
// }
// void Window::drawBG(){
//     float drawW = bg.width * SCALE;
//     float drawH = bg.height * SCALE;
//     float offsetX = (width  - drawW) / 2.0f;
//     float offsetY = (height - drawH) / 2.0f;
//     DrawTextureEx(bg, {offsetX, offsetY}, 0.0f, SCALE, WHITE);
// }

// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "Window.h"

void Window::initializeWindow() {
  // Inicializa la ventana
  InitWindow(WIDTH, HEIGHT, "Pixel pong");

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
  float offsetX = (WIDTH  - drawW) / 2.0f;
  float offsetY = (HEIGHT - drawH) / 2.0f;
  DrawTextureEx(game_background, {offsetX, offsetY}, 0.0f, SCALE, WHITE);
}
