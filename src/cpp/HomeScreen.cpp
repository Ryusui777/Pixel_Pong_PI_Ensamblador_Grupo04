#include "HomeScreen.h"


void HomeScreen::init(){
    this->blurBG = LoadTexture(bg_paht);
    this->start.init((char*)start_path, startPos);
    this->logo.init((char*)logoPath, logoPos);
}


void HomeScreen::draw(){
    // Background
    float drawW = blurBG.width * SCALE;
    float drawH = blurBG.height * SCALE;
    float offsetX = (WIDTH  - drawW) / 2.0f;
    float offsetY = (HEIGHT - drawH) / 2.0f;
    DrawTextureEx(blurBG, {offsetX, offsetY}, 0.0f, SCALE, WHITE);

    this->start.draw();
    this->logo.draw();
}

void HomeScreen::started(byte& startVar){
    startVar = (this->start.isClicked())? 1 : startVar;
    if(IsKeyDown(KEY_ENTER)) startVar = 1;
}