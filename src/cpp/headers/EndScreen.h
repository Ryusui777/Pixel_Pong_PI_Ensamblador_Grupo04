#pragma once

#include "shared.h"
#include "Button.h"



class EndScreen{
    private:
        // Paths hacia todos los recursos graficos
        const char* bg_path = "res/endScreen/bg.png";
        const char* playAgain_path = "res/endScreen/playAgain.png";

        // Members
        Texture2D blur_bg;
        Button playAgain;

};