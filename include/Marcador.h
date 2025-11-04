#pragma once
#include "shared.h"
#include <iomanip>
#include <sstream>
#include <iostream>


class Marcador {
    Texture2D numbers[10];
    Texture2D numbers2[10];
    Vector2 position;


    void drawElement(Texture2D& txt, Vector2 pos){
        Rectangle src{ 0, 0, (float)txt.width, (float)txt.height };
        Rectangle dst{ pos.x, pos.y,
        txt.width * SCALE, txt.height * SCALE };
        Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
        DrawTexturePro(txt, src, dst, origin, 0.0f, WHITE);
    }


    public:

    void init(Vector2 position){
        this->position = position;

        numbers[0] = LoadTexture((char*)"assets/mainGame/numbers/number009.png");
        numbers2[0] = LoadTexture((char*)"assets/mainGame/numbers/number009.png");

        SetTextureFilter(numbers[0], TEXTURE_FILTER_POINT);
        for(int i = 0; i < 9; ++i){
            std::ostringstream fileName;
            fileName << "assets/mainGame/numbers/number00" << i << ".png";
            numbers[i+1] = LoadTexture(fileName.str().c_str()); 
            numbers2[i+1] = LoadTexture(fileName.str().c_str()); 
            SetTextureFilter(numbers[i+1], TEXTURE_FILTER_POINT);
        }
    }

    void draw(int number){
        Vector2 positionFirstNumber{
            .x = (position.x-(numbers[0].width*SCALE/2)),
            .y = position.y
        };
        Vector2 positionSecoundNumber{
            .x = (position.x+(numbers[0].width*SCALE/2)),
            .y = position.y
        };

        int orinal = number;
        while(number > 10){
            number/=10;
        }

        drawElement(numbers[number], positionFirstNumber);
        if(orinal > 10){
            drawElement(numbers2[orinal-number*10], positionSecoundNumber);
        }
        else drawElement(numbers2[orinal-number*10], positionSecoundNumber);
    }
    

};













