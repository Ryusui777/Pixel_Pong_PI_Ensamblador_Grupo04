//Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
#include <gtest/gtest.h>
#include <cmath>

//Definir Vector2 para tests
struct Vector2 {
  float x;
  float y;
};

//Declarar funciones de ensamblador que se van a testear
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

  void pelotaMove();
  void resetBall();
  int isBallOpossingPlayer();
  void pelotaReboto();
  void setDifficulty(int difficulty);
  
  //getters y setters nuevos
  float getCurrentAngle();
  int getIsOpposingPlayer();
  int getGameDifficulty();
  void setCurrentAngle(float angle);
}

/* PRUEBAS PARA EL JUGADOR */

//Clase de prueba para movimiento de jugador
class PlayerMovementTest : public ::testing::Test {
 protected:
  Vector2 position;

  //Se inicializa la posición del jugador para la prueba
  void SetUp() override {
    //Centro de la pantalla
    position = {640.0f, 360.0f};
    initPlayerMovement(50.0f, 670.0f, &position);
  }
};

//Prueba: Mover jugador hacia arriba
TEST_F(PlayerMovementTest, MoveUpDecreasesY) {
  float initialY = position.y;
  //Se llama a funcion de ensamblador
  moverJugadorArriba();

  //Se verifica que el jugador se mueva hacia arriba
  EXPECT_LT(position.y, initialY)
    << "El jugador deberia moverse hacia arriba (Y menor)";
  //Se verifica que se haya movido la cantidad correcta de pixeles
  EXPECT_FLOAT_EQ(position.y, initialY - 8.0f)
    << "El jugador deberia moverse 8 pixeles";
}

//Prueba: Mover jugador hacia abajo
TEST_F(PlayerMovementTest, MoveDownIncreasesY) {
  float initialY = position.y;
  //Se llama a funcion de ensamblador
  moverJugadorAbajo();

  //Se verifica que el jugador se mueva hacia abajo
  EXPECT_GT(position.y, initialY)
    << "El jugador deberia moverse hacia abajo (Y mayor)";
  //Se verifica que se haya movido la cantidad correcta de pixeles
  EXPECT_FLOAT_EQ(position.y, initialY + 8.0f)
    << "El jugador deberia moverse 8 pixeles";
}

//Prueba: No traspasar límites de la ventana por arriba
TEST_F(PlayerMovementTest, CannotMoveAboveUpperLimit) {
  position.y = 50.0f;  //Se pone al jugador el límite superior
  moverJugadorArriba();   //Se intenta moverlo más arriba

  //Se verifica que no se haya movido
  EXPECT_FLOAT_EQ(position.y, 50.0f)
    << "El jugador no deberia atravesar el límite superior";
}

//Prueba: No traspasar límites de la ventana por abajo
TEST_F(PlayerMovementTest, CannotMoveBelowLowerLimit) {
  position.y = 670.0f;  //Se pone al jugador el límite inferior
  moverJugadorAbajo();  //Se intenta moverlo más abajo

  //Se verifica que no se haya movido
  EXPECT_FLOAT_EQ(position.y, 670.0f)
    << "El jugador no deberia atravesar el límite inferior";
}

//Prueba: Se puede mover al jugador más de una vez
TEST_F(PlayerMovementTest, MultipleMovements) {
  float initialY = position.y;

  //Mover hacia arriba 2 veces
  for (int i = 0; i < 2; i++) {
    moverJugadorArriba();
  }

  EXPECT_FLOAT_EQ(position.y, initialY - 16.0f)
    << "2 movimientos arriba son 16 pixeles";

  //Mover hacia abajo 3 veces
  for (int i = 0; i < 3; i++) {
    moverJugadorAbajo();
  }

  EXPECT_FLOAT_EQ(position.y, initialY + 8.0f)
    << "Resultado total: -16 + 24 = +8 pixeles";
}

/* PRUEBAS PARA EL BOT */

//Clase de prueba para movimiento del bot
class BotMovementTest : public ::testing::Test {
 protected:
  Vector2 position;
  void SetUp() override {
    //Se pone en el centro
    position = {640.0f, 360.0f};
    initBotMovement(50.0f, 670.0f, &position);
  }
};

//Prueba: Verificar que el bot se mueve
TEST_F(BotMovementTest, BotMovesAutomatically) {
  float initialY = position.y;
  moverBot();
  EXPECT_NE(position.y, initialY)
    << "El bot deberia moverse";
}

/* PRUEBAS PARA LA BOLA */

//Clase de prueba para comportamiento de la pelota con las paletas
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

  //Helper para simular una colisión con paleta del jugador
  void simulatePlayerPaddleHit() {
    //Colocar pelota cerca del jugador
    ballPosition.x = 1190.0f;  //10 pixeles antes de la paleta
    ballPosition.y = 360.0f;  //Misma altura que paleta
    ballVelocity.x = 8.0f;  //Moviéndose hacia la derecha
    ballVelocity.y = 0.0f;
  }

  //Helper para simular una colisión con paleta del bot
  void simulateBotPaddleHit() {
    //Colocar pelota cerca del bot
    ballPosition.x = 110.0f;  //10 pixeles después de la paleta
    ballPosition.y = 360.0f;  //Misma altura que paleta
    ballVelocity.x = -8.0f;  //Moviéndose hacia la izquierda
    ballVelocity.y = 0.0f;
  }
};

//Prueba: Pelota rebota al tocar paleta del jugador (no la atraviesa)
TEST_F(BallCollisionTest, BallBouncesOffPlayerPaddle) {
  //Simular contacto con paleta
  simulatePlayerPaddleHit();
  float initialVelX = ballVelocity.x;  //Trayectoria (hacia derecha)
  //Rebote
  pelotaReverseX();

  //Verificar que la velocidad X se invirtio (es decir, bola va hacia la izq.)
  EXPECT_FLOAT_EQ(ballVelocity.x, -initialVelX)
    << "La velocidad X deberia invertirse al rebotar en la paleta del jugador";

  //Verificar que no atraviese paleta
  EXPECT_LT(ballVelocity.x, 0.0f)
    << "Después del contacto, la pelota deberia rebotar";
}

//Prueba: Pelota rebota al tocar paleta del bot (no la atraviesa)
TEST_F(BallCollisionTest, BallBouncesOffBotPaddle) {
  //Simular contacto con paleta
  simulateBotPaddleHit();
  float initialVelX = ballVelocity.x;  //Trayectoria (hacia izquierda)
  //Simular rebote
  pelotaReverseX();

  //Verificar que la velocidad X se invirtio (La bola va hacia el jugador)
  EXPECT_FLOAT_EQ(ballVelocity.x, -initialVelX)
    << "La velocidad X deberia invertirse al rebotar en la paleta del bot";

  //Verificar que no atraviese paleta
  EXPECT_GT(ballVelocity.x, 0.0f)
    << "Después del contacto, la pelota deberia rebotar";
}

//Prueba: Pelota rebota en el margen superior
TEST_F(BallCollisionTest, BallBouncesAtTopBoundary) {
  //Bola va para arriba
  ballPosition.y = 15.0f;
  ballVelocity.x = 5.0f;
  ballVelocity.y = -8.0f;  //Velocidad hacia arriba

  float initialVelY = ballVelocity.y;  //-8.0

  //Simular rebote en margen superior
  pelotaReverseY();

  //Verificar que la velocidad de Y se invirtio
  EXPECT_FLOAT_EQ(ballVelocity.y, -initialVelY)
    << "La velocidad Y deberia invertirse al rebotar en margen superior";

  //Verificar que ahora va hacia abajo (velocidad positiva)
  EXPECT_GT(ballVelocity.y, 0.0f)
    << "Después del rebote, la pelota deberia ir hacia abajo";
}

//Prueba: Pelota rebota en el margen inferior
TEST_F(BallCollisionTest, BallBouncesAtBottomBoundary) {
  //Bola va para abajo
  ballPosition.y = 705.0f;
  ballVelocity.x = 5.0f;
  ballVelocity.y = 8.0f;  //Velocidad hacia abajo

  float initialVelY = ballVelocity.y;  //8.0

  //Simular rebote en margen inferior
  pelotaReverseY();

  //Verificar que la velocidad de Y se invirtio
  EXPECT_FLOAT_EQ(ballVelocity.y, -initialVelY)
    << "La velocidad Y deberia invertirse al rebotar en margen inferior";

  //Verificar que ahora va hacia arriba (velocidad negativa)
  EXPECT_LT(ballVelocity.y, 0.0f)
    << "Después del rebote, la pelota deberia ir hacia arriba";
}




class BallResetTest : public ::testing::Test {
protected:
    Vector2 ballVelocity;
    Vector2 ballPosition;
    
    void SetUp() override {
        ballVelocity = {0.0f, 0.0f};
        ballPosition = {640.0f, 360.0f};
        initPelotaMovement(&ballVelocity, &ballPosition, 10.0f, 710.0f);
    }
};

class BallOppositionTest : public ::testing::Test {
protected:
    Vector2 ballVelocity;
    Vector2 ballPosition;
    
    void SetUp() override {
        ballVelocity = {0.0f, 0.0f};
        ballPosition = {640.0f, 360.0f};
        initPelotaMovement(&ballVelocity, &ballPosition, 10.0f, 710.0f);
    }
};

//Pruebas para pelotaMove
TEST_F(BallResetTest, PelotaMoveUpdatesPosition) {
    ballVelocity = {5.0f, 3.0f};
    ballPosition = {100.0f, 200.0f};
    
    pelotaMove();
    
    EXPECT_FLOAT_EQ(ballPosition.x, 105.0f);
    EXPECT_FLOAT_EQ(ballPosition.y, 203.0f);
}

TEST_F(BallResetTest, PelotaMoveWithNegativeVelocity) {
    ballVelocity = {-2.0f, -1.0f};
    ballPosition = {50.0f, 60.0f};
    
    pelotaMove();
    
    EXPECT_FLOAT_EQ(ballPosition.x, 48.0f);
    EXPECT_FLOAT_EQ(ballPosition.y, 59.0f);
}

TEST_F(BallResetTest, PelotaMoveWithZeroVelocity) {
    ballVelocity = {0.0f, 0.0f};
    ballPosition = {100.0f, 100.0f};
    
    pelotaMove();
    
    EXPECT_FLOAT_EQ(ballPosition.x, 100.0f);
    EXPECT_FLOAT_EQ(ballPosition.y, 100.0f);
}

//Pruebas para resetBall
TEST_F(BallResetTest, ResetBallCreatesValidVelocity) {
    resetBall();
    
    float speed = sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
    EXPECT_NEAR(speed, 10.0f, 0.1f)
        << "La rapidez deberia ser aproximadamente 10 después del reset";
}

TEST_F(BallResetTest, ResetBallAvoidsForbiddenAngles) {
    //Probar multiples resets para verificar que evita bandas prohibidas
    for (int i = 0; i < 10; i++) {
        resetBall();
        float angle = getCurrentAngle();
        
        //Verificar que no está en bandas prohibidas: [60-120] y [240-300]
        bool inForbiddenBand1 = (angle >= 60.0f && angle <= 120.0f);
        bool inForbiddenBand2 = (angle >= 240.0f && angle <= 300.0f);
        
        EXPECT_FALSE(inForbiddenBand1) 
            << "angulo " << angle << " no deberia estar en banda 60-120";
        EXPECT_FALSE(inForbiddenBand2) 
            << "angulo " << angle << " no deberia estar en banda 240-300";
    }
}

TEST_F(BallResetTest, ResetBallUpdatesOppositionFlag) {
    resetBall();
    
    int isOpposing = getIsOpposingPlayer();
    float angle = getCurrentAngle();
    
    //Verificar que la bandera coincide con el angulo
    bool shouldOppose = (angle >= 90.0f && angle <= 270.0f);
    EXPECT_EQ(isOpposing, shouldOppose ? 1 : 0) 
        << "La bandera de oposición deberia coincidir con el angulo " << angle;
}

//Pruebas para isBallOpossingPlayer
TEST_F(BallOppositionTest, OppositionForRightwardAngles) {
    //angulos que NO deberian oponer
    float testAngles[] = {0.0f, 45.0f, 89.0f, 271.0f, 315.0f, 359.0f};
    
    for (float angle : testAngles) {
        setCurrentAngle(angle);
        EXPECT_EQ(isBallOpossingPlayer(), 0) 
            << "angulo " << angle << " no deberia oponer al jugador";
    }
}




//Pruebas para pelotaReboto
TEST_F(BallOppositionTest, PelotaRebotoTogglesOpposition) {
    setCurrentAngle(45.0f); //No opone - deberia retornar 0
    int initial = isBallOpossingPlayer();
    
    pelotaReboto();
    int afterFirst = isBallOpossingPlayer();
    
    pelotaReboto();
    int afterSecond = isBallOpossingPlayer();
    
    EXPECT_NE(initial, afterFirst) 
        << "Primer rebote deberia cambiar la oposición";
    EXPECT_EQ(initial, afterSecond) 
        << "Segundo rebote deberia restaurar el estado original";
}

TEST_F(BallOppositionTest, PelotaRebotoPreservesAngle) {
    //Verificar que reboto no cambia el angulo
    float originalAngle = 45.0f;
    setCurrentAngle(originalAngle);
    
    pelotaReboto();
    
    EXPECT_FLOAT_EQ(getCurrentAngle(), originalAngle) 
        << "pelotaReboto no deberia cambiar el angulo";
}



//Pruebas para setDifficulty
TEST(DifficultyTest, SetDifficultyAllLevels) {
    setDifficulty(0); //Easy
    EXPECT_EQ(getGameDifficulty(), 0);
    
    setDifficulty(1); //Medium
    EXPECT_EQ(getGameDifficulty(), 1);
    
    setDifficulty(2); //Hard
    EXPECT_EQ(getGameDifficulty(), 2);
}


//prueba integrada
TEST_F(BallResetTest, WorkflowTest) {
    //test de flujo completo: reset -> move -> reverse -> reboto
    resetBall();
    
    Vector2 initialPos = ballPosition;
    Vector2 initialVel = ballVelocity;
    
    //Mover la pelota
    pelotaMove();
    EXPECT_NE(ballPosition.x, initialPos.x);
    EXPECT_NE(ballPosition.y, initialPos.y);
    
    //Reversar en X
    pelotaReverseX();
    EXPECT_FLOAT_EQ(ballVelocity.x, -initialVel.x);
    
    //Hacer rebote
    int oppositionBefore = isBallOpossingPlayer();
    pelotaReboto();
    int oppositionAfter = isBallOpossingPlayer();
    EXPECT_NE(oppositionBefore, oppositionAfter);
}

