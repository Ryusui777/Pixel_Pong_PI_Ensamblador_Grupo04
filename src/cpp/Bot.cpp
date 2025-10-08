#include "Bot.h"


void Bot::init(){
    // Carga la textura del jugador
    this->texture = LoadTexture((char*)bot_path);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    
    // Centra el bot
    const float margin = 5.0f;
    position.y = HEIGHT / 2.0f;  
    position.x = texture.width * SCALE + margin;
}


void Bot::draw(){
    Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };
    Rectangle dst{ position.x, position.y,
                   texture.width * SCALE, texture.height * SCALE };
    Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}