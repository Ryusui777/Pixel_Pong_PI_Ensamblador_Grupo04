// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#pragma once
#include "raylib.h"
#include "shared.h"

/**
 * @brief Clase para manejar un slider horizontal
 * @remark Esta clase la hice mayoritariamente con IA (atributos y definiciones
 * de métodos) porque no tenía claro cómo hacer un slider.
 * @author Enrique
 */
class Slider {
 private:
  Vector2 position;  // Posición del slider
  float width;  // Ancho del slider
  float height;  // Alto de la barra
  float minValue;  // Valor mínimo
  float maxValue;  // Valor máximo
  float currentValue;  // Valor actual
  bool isDragging;  // Si el usuario está arrastrando

  Color barColor;  // Color de la barra
  Color handleColor;  // Color del handle
  Color fillColor;  // Color del relleno

 public:
  /**
   * @brief Constructor
   */
  Slider();

  /**
   * @brief Inicializa el slider
   * @param pos Posición del slider
   * @param w Ancho del slider
   * @param h Alto de la barra
   * @param minVal Valor mínimo
   * @param maxVal Valor máximo
   * @param initialVal Valor inicial
   */
  void initializeSlider(Vector2 pos, float w, float h, float minVal,
    float maxVal, float initialVal);

  /**
   * @brief Actualiza el estado del slider (debe llamarse cada frame)
   */
  void updateSlider();

  /**
   * @brief Dibuja el slider en pantalla
   */
  void drawSlider();

  /**
   * @brief Obtiene el valor actual del slider
   * @return Valor actual
   */
  float getValue() const {
    return currentValue;
  }

  /**
   * @brief Establece el valor del slider
   * @param value Nuevo valor
   */
  void setValue(float value);
};
