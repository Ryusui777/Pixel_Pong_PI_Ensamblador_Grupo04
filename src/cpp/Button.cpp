#include "Button.h"


Button::Button(){

}

void Button::init(char* imgPath, Vector2 vec){
    position = vec;
    this->texture = LoadTexture(imgPath);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
}
void Button::draw(){

    Rectangle src{ 0, 0, (float)texture.width, (float)texture.height };

    Rectangle dst{ position.x, position.y,
                   texture.width * SCALE, texture.height * SCALE };
    Vector2 origin{ dst.width/2.0f, dst.height/2.0f };
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

byte Button::isHovered(){
    float scale = 5.0f;
    // Build the same dst/origin you use to draw
    Rectangle dst{ position.x, position.y,
                   texture.width * SCALE, texture.height * SCALE };
    Vector2 origin{ dst.width/2.0f, dst.height/2.0f };

    // Convert to a top-left anchored rect for hit-test
    Rectangle bounds{ dst.x - origin.x, dst.y - origin.y, dst.width, dst.height };

    Vector2 m = GetMousePosition();
    return CheckCollisionPointRec(m, bounds);
}