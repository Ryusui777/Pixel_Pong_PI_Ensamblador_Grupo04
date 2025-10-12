#include "HomeScreen.h"


void HomeScreen::init(){
    this->start.init((char*)start_path, startPos);
}


void HomeScreen::draw(){
    this->start.draw();
}

void HomeScreen::started(byte& startVar){
    startVar = (this->start.isClicked())? 1 : startVar;
    if(IsKeyDown(KEY_ENTER)) startVar = 1;
}