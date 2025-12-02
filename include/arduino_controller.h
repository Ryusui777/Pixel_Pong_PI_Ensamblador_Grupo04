// Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
// Adaptado de Sleyter Angulo por Enrique Ramírez con ayuda de IA (Claude)
#ifndef ARDUINO_CONTROLLER_H
#define ARDUINO_CONTROLLER_H

#include <string>
#include <termios.h>

class ArduinoController {
 public:
  ArduinoController();
  ~ArduinoController();

  bool connect(const std::string& port);
  char readCommand();

 private:
  int serial_port;
  bool connected;
};

#endif
