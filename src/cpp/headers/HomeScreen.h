#pragma once 

#include "Button.h"
#include "Label.h"
#include "shared.h"


class HomeScreen{
    private:
        const char* start_path="res/homeScreen/start.png"; 
        const char* logoPath="res/homeScreen/Logo.png";
        const char* bg_paht="res/homeScreen/bg.png";

        Vector2 logoPos= {
            .x = WIDTH/2.0f,
            .y = HEIGHT/4.0f
        };
        
        Button start;
        Label logo;
        Texture2D blurBG;
    public:
        void init();
        void draw();
        void started(byte&);

};