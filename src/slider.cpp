// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include "slider.h"
#include <algorithm>

Slider::Slider() {
  isDragging = false;
  barColor = {200, 200, 200, 255};  // Gris
  handleColor = {255, 255, 255, 255};  // Blanco
  fillColor = {100, 150, 255, 255};  // Azul
}

void Slider::initializeSlider(Vector2 pos, float w, float h, float minVal,
  float maxVal, float initialVal) {
  position = pos;
  width = w;
  height = h;
  minValue = minVal;
  maxValue = maxVal;
  currentValue = std::max(minVal, std::min(maxVal, initialVal));
}

void Slider::updateSlider() {
  Vector2 mousePos = GetMousePosition();

  // Calcular la posición del handle
  float normalizedValue = (currentValue - minValue) / (maxValue - minValue);
  float handleX = position.x + normalizedValue * width;
  float handleY = position.y + height / 2.0f;
  float handleRadius = height * 1.5f;

  // Verificar si el mouse está sobre el handle
  bool mouseOverHandle = CheckCollisionPointCircle(mousePos, {handleX, handleY},
    handleRadius);

  // Verificar si el mouse está sobre la barra
  Rectangle barRect = {position.x, position.y, width, height};
  bool mouseOverBar = CheckCollisionPointRec(mousePos, barRect);

  // Empezar a arrastrar
  if ((mouseOverHandle || mouseOverBar) &&
    IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    isDragging = true;
  }

  // Dejar de arrastrar
  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    isDragging = false;
  }

  // Actualizar valor mientras se arrastra
  if (isDragging) {
    float relativeX = mousePos.x - position.x;
    relativeX = std::max(0.0f, std::min(width, relativeX));
    float normalizedPos = relativeX / width;
    currentValue = minValue + normalizedPos * (maxValue - minValue);
  }
}

void Slider::drawSlider() {
  // Dibujar la barra de fondo
  DrawRectangleRounded({position.x, position.y, width, height},
    0.5f, 8, barColor);

  // Dibujar la barra de progreso (parte llena)
  float normalizedValue = (currentValue - minValue) / (maxValue - minValue);
  float fillWidth = normalizedValue * width;
  if (fillWidth > 0) {
    DrawRectangleRounded({position.x, position.y, fillWidth, height},
      0.5f, 8, fillColor);
  }

  // Calcular posición del handle
  float handleX = position.x + normalizedValue * width;
  float handleY = position.y + height / 2.0f;
  float handleRadius = height * 1.5f;

  // Dibujar el handle (círculo)
  DrawCircleV({handleX, handleY}, handleRadius, handleColor);
  DrawCircleV({handleX, handleY}, handleRadius - 2, fillColor);

  // Dibujar el valor actual
  char valueText[32];
  snprintf(valueText, sizeof(valueText), "%d", (int)(currentValue));
  int textWidth = MeasureText(valueText, 20);
  DrawText(valueText, position.x + width / 2 - textWidth / 2, position.y - 30
    , 20, WHITE);
}

void Slider::setValue(float value) {
  currentValue = std::max(minValue, std::min(maxValue, value));
}
