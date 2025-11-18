const int JOY_Y = A0;

void setup() {
  Serial.begin(9600);
  pinMode(JOY_Y, INPUT);
}

void loop() {
  int yValue = analogRead(JOY_Y);
  
  if (yValue > 700) {
    Serial.println('U');  // Arriba
  } else if (yValue < 300) {
    Serial.println('D');  // Abajo
  }
  
  delay(50);
}
