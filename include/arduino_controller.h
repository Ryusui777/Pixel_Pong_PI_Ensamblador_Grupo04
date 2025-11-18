#ifndef ARDUINO_CONTROLLER_HH
#define ARDUINO_CONTROLLER_HH

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