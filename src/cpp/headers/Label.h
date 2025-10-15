#include "shared.h"

/**
 * @brief para mostrar el logo
 */
class Label {
  private:
  Texture2D texture;
  Vector2 position;
  public:
  void init(char*, Vector2);
  void draw();
};
