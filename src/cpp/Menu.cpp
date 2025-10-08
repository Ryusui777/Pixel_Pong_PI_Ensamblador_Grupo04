#include "Menu.h"


void Menu::init(){
    this->blurBG = LoadTexture(bg_path);
    this->homeButton.init((char*)home_path, homePos);
    this->resumeButton.init((char*)resume_path, resumePos);
}

void Menu::draw(){
    // Background
    float drawW = blurBG.width * SCALE;
    float drawH = blurBG.height * SCALE;
    float offsetX = (WIDTH  - drawW) / 2.0f;
    float offsetY = (HEIGHT - drawH) / 2.0f;
    DrawTextureEx(blurBG, {offsetX, offsetY}, 0.0f, SCALE, WHITE);

    // UI elements
    this->homeButton.draw();
    this->resumeButton.draw();
}