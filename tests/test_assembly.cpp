// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include <gtest/gtest.h>
#include <cmath>

// Definir Vector2 para tests
struct Vector2 {
  float x;
  float y;
};

// Declarar funciones de ensamblador que se van a testear
extern "C" {
  void moverJugadorArriba();
  void moverJugadorAbajo();
  void initPlayerMovement(float upperLimit, float lowerLimit
    , Vector2* position);

  void moverBot();
  void initBotMovement(float upperLimit, float lowerLimit, Vector2* position);
}

/* PRUEBAS PARA EL JUGADOR */

// Clase de prueba para movimiento de jugador
class PlayerMovementTest : public ::testing::Test {
 protected:
  Vector2 position;

  // Se inicializa la posición del jugador para la prueba
  void SetUp() override {
    // Centro de la pantalla
    position = {640.0f, 360.0f};
    initPlayerMovement(50.0f, 670.0f, &position);
  }
};

// Prueba: Mover jugador hacia arriba
TEST_F(PlayerMovementTest, MoveUpDecreasesY) {
  float initialY = position.y;
  // Se llama a función de ensamblador
  moverJugadorArriba();
  
  // Se verifica que el jugador se mueva hacia arriba
  EXPECT_LT(position.y, initialY) 
    << "El jugador debería moverse hacia arriba (Y menor)";
  // Se verifica que se haya movido la cantidad correcta de píxeles
  EXPECT_FLOAT_EQ(position.y, initialY - 8.0f) 
    << "El jugador debería moverse 8 píxeles";
}

// Prueba: Mover jugador hacia abajo
TEST_F(PlayerMovementTest, MoveDownIncreasesY) {
  float initialY = position.y;
  // Se llama a función de ensamblador
  moverJugadorAbajo();
  
  // Se verifica que el jugador se mueva hacia abajo
  EXPECT_GT(position.y, initialY) 
    << "El jugador debería moverse hacia abajo (Y mayor)";
  // Se verifica que se haya movido la cantidad correcta de píxeles
  EXPECT_FLOAT_EQ(position.y, initialY + 8.0f) 
    << "El jugador debería moverse 8 píxeles";
}

// Prueba: No traspasar límites de la ventana por arriba
TEST_F(PlayerMovementTest, CannotMoveAboveUpperLimit) {
  position.y = 50.0f;  // Se pone al jugador el límite superior
  moverJugadorArriba();   // Se intenta moverlo más arriba
  
  // Se verifica que no se haya movido
  EXPECT_FLOAT_EQ(position.y, 50.0f) 
    << "El jugador no debería atravesar el límite superior";
}

// Prueba: No traspasar límites de la ventana por abajo
TEST_F(PlayerMovementTest, CannotMoveBelowLowerLimit) {
  position.y = 670.0f;  // Se pone al jugador el límite inferior
  moverJugadorAbajo();  // Se intenta moverlo más abajo
  
  // Se verifica que no se haya movido
  EXPECT_FLOAT_EQ(position.y, 670.0f) 
    << "El jugador no debería atravesar el límite inferior";
}

// Prueba: Se puede mover al jugador más de una vez
TEST_F(PlayerMovementTest, MultipleMovements) {
  float initialY = position.y;
  
  // Mover hacia arriba 2 veces
  for (int i = 0; i < 2; i++) {
    moverJugadorArriba();
  }

  EXPECT_FLOAT_EQ(position.y, initialY - 16.0f) 
    << "2 movimientos arriba son 16 píxeles";
  
  // Mover hacia abajo 3 veces
  for (int i = 0; i < 3; i++) {
    moverJugadorAbajo();
  }

  EXPECT_FLOAT_EQ(position.y, initialY + 8.0f) 
    << "Resultado total: -16 + 24 = +8 píxeles";
}

/* PRUEBAS PARA EL BOT */

// Clase de prueba para movimiento del bot
class BotMovementTest : public ::testing::Test {
 protected:
  Vector2 position;
  void SetUp() override {
    // Se pone en el centro
    position = {640.0f, 360.0f};
    initBotMovement(50.0f, 670.0f, &position);
  }
};

// Prueba: Verificar que el bot se mueve de automáticamente
TEST_F(BotMovementTest, BotMovesAutomatically) {
  float initialY = position.y;
  moverBot();
  EXPECT_NE(position.y, initialY)
    << "El bot debería moverse automáticamente";
}
