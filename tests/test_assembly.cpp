// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
/**
 * @note Se usó IA (Claude y Deepseek) par aconsultar por recomendaciones de
 * casos de prueba unitarios; esto antes de que el profesor nos indicara que no
 * eran estas el tipo de pruebas requeridas.
 */

#include <gtest/gtest.h>

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

  void pelotaReverseX();
  void pelotaReverseY();
  void initPelotaMovement(Vector2* velocity, Vector2* position
    , float upperLimit, float lowerLimit);
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

// Prueba: Verificar que el bot se mueve
TEST_F(BotMovementTest, BotMovesAutomatically) {
  float initialY = position.y;
  moverBot();
  EXPECT_NE(position.y, initialY)
    << "El bot debería moverse";
}

/* PRUEBAS PARA LA BOLA */

// Clase de prueba para comportamiento de la pelota con las paletas
class BallCollisionTest : public ::testing::Test {
 protected:
  Vector2 ballVelocity;
  Vector2 ballPosition;
  Vector2 playerPosition;
  Vector2 botPosition;

  void SetUp() override {
    ballVelocity = {0.0f, 0.0f};
    ballPosition = {640.0f, 360.0f};
    playerPosition = {1200.0f, 360.0f};
    botPosition = {100.0f, 360.0f};

    initPelotaMovement(&ballVelocity, &ballPosition, 10.0f, 710.0f);
    initPlayerMovement(50.0f, 670.0f, &playerPosition);
    initBotMovement(50.0f, 670.0f, &botPosition);
  }

  // Helper para simular una colisión con paleta del jugador
  void simulatePlayerPaddleHit() {
    // Colocar pelota cerca del jugador
    ballPosition.x = 1190.0f;  // 10 píxeles antes de la paleta
    ballPosition.y = 360.0f;  // Misma altura que paleta
    ballVelocity.x = 8.0f;  // Moviéndose hacia la derecha
    ballVelocity.y = 0.0f;
  }

  // Helper para simular una colisión con paleta del bot
  void simulateBotPaddleHit() {
    // Colocar pelota cerca del bot
    ballPosition.x = 110.0f;  // 10 píxeles después de la paleta
    ballPosition.y = 360.0f;  // Misma altura que paleta
    ballVelocity.x = -8.0f;  // Moviéndose hacia la izquierda
    ballVelocity.y = 0.0f;
  }
};

// Prueba: Pelota rebota al tocar paleta del jugador (no la atraviesa)
TEST_F(BallCollisionTest, BallBouncesOffPlayerPaddle) {
  // Simular contacto con paleta
  simulatePlayerPaddleHit();
  float initialVelX = ballVelocity.x;  // Trayectoria (hacia derecha)
  // Rebote
  pelotaReverseX();

  // Verificar que la velocidad X se invirtió (es decir, bola va hacia la izq.)
  EXPECT_FLOAT_EQ(ballVelocity.x, -initialVelX)
    << "La velocidad X debería invertirse al rebotar en la paleta del jugador";

  // Verificar que no atraviese paleta
  EXPECT_LT(ballVelocity.x, 0.0f)
    << "Después del contacto, la pelota debería rebotar";
}

// Prueba: Pelota rebota al tocar paleta del bot (no la atraviesa)
TEST_F(BallCollisionTest, BallBouncesOffBotPaddle) {
  // Simular contacto con paleta
  simulateBotPaddleHit();
  float initialVelX = ballVelocity.x;  // Trayectoria (hacia izquierda)
  // Simular rebote
  pelotaReverseX();

  // Verificar que la velocidad X se invirtió (La bola va hacia el jugador)
  EXPECT_FLOAT_EQ(ballVelocity.x, -initialVelX)
    << "La velocidad X debería invertirse al rebotar en la paleta del bot";

  // Verificar que no atraviese paleta
  EXPECT_GT(ballVelocity.x, 0.0f)
    << "Después del contacto, la pelota debería rebotar";
}

// Prueba: Pelota rebota en el margen superior
TEST_F(BallCollisionTest, BallBouncesAtTopBoundary) {
  // Bola va para arriba
  ballPosition.y = 15.0f;
  ballVelocity.x = 5.0f;
  ballVelocity.y = -8.0f;  // Velocidad hacia arriba

  float initialVelY = ballVelocity.y;  // -8.0

  // Simular rebote en margen superior
  pelotaReverseY();

  // Verificar que la velocidad de Y se invirtió
  EXPECT_FLOAT_EQ(ballVelocity.y, -initialVelY)
    << "La velocidad Y debería invertirse al rebotar en margen superior";

  // Verificar que ahora va hacia abajo (velocidad positiva)
  EXPECT_GT(ballVelocity.y, 0.0f)
    << "Después del rebote, la pelota debería ir hacia abajo";
}

// Prueba: Pelota rebota en el margen inferior
TEST_F(BallCollisionTest, BallBouncesAtBottomBoundary) {
  // Bola va para abajo
  ballPosition.y = 705.0f;
  ballVelocity.x = 5.0f;
  ballVelocity.y = 8.0f;  // Velocidad hacia abajo

  float initialVelY = ballVelocity.y;  // 8.0

  // Simular rebote en margen inferior
  pelotaReverseY();

  // Verificar que la velocidad de Y se invirtió
  EXPECT_FLOAT_EQ(ballVelocity.y, -initialVelY)
    << "La velocidad Y debería invertirse al rebotar en margen inferior";

  // Verificar que ahora va hacia arriba (velocidad negativa)
  EXPECT_LT(ballVelocity.y, 0.0f)
    << "Después del rebote, la pelota debería ir hacia arriba";
}
