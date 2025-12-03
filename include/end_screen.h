// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "shared.h"
#include "button.h"

class EndScreen {
 private:
  // Paths hacia todos los recursos graficos
  const char* bg_path = "assets/endScreen/home_background.png";
  const char* playAgain_path = "assets/endScreen/playAgain.png";

  // Members
  Texture2D blur_bg;
  Button playAgain;
};
