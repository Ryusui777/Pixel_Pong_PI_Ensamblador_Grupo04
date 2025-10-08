#include "Window.h"

#include "Window.h"

void Window::init(){

    // Dimesiones de la ventana
    this->width = WIDTH;
    this->height = HEIGHT;

    // Inicializa la ventana
	InitWindow(width, height, "Pixel pong");

    // Carga la textura del bg
    bg = LoadTexture(bg_path);

    // Establece la velocidad de refrescamiento
    SetTargetFPS(60);
}


void Window::beginDraw(){
        BeginDrawing();
            drawBG();
}

void Window::draw(Texture2D texture, Vector2 pos){
    DrawTexture(texture, pos.x, pos.y, BLACK);
}

void Window::endDraw(){
    EndDrawing();
}
void Window::drawBG(){
    float drawW = bg.width * SCALE;
    float drawH = bg.height * SCALE;
    float offsetX = (width  - drawW) / 2.0f;
    float offsetY = (height - drawH) / 2.0f;
    DrawTextureEx(bg, {offsetX, offsetY}, 0.0f, SCALE, WHITE);
}
