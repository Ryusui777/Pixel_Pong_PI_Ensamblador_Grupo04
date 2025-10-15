
#include "shared.h"


class Label {
    private:
    Texture2D texture;
    Vector2 position;
    public:
    void init(char*, Vector2);
    void draw();
};