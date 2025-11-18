const int JOY_Y = A0;

void setup() {
  Serial.begin(9600);
  pinMode(JOY_Y, INPUT);
}

void loop() {
  int yValue = analogRead(JOY_Y);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

=======
  
>>>>>>> 5f6bb0d (Se agregan archivos para uso de joystick)
=======

>>>>>>> 2aa1e46 ( Se actualiza velocidad de recorrido del joystick)
=======
  
>>>>>>> 5f6bb0d (Se agregan archivos para uso de joystick)
  if (yValue > 700) {
    Serial.println('U');  // Arriba
  } else if (yValue < 300) {
    Serial.println('D');  // Abajo
  }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

  delay(10);
=======
  
  delay(50);
>>>>>>> 5f6bb0d (Se agregan archivos para uso de joystick)
=======

  delay(10);
>>>>>>> 2aa1e46 ( Se actualiza velocidad de recorrido del joystick)
=======
  
  delay(50);
>>>>>>> 5f6bb0d (Se agregan archivos para uso de joystick)
}
