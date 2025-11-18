// Adaptado de Sleyter Angulo por Enrique Ramírez con ayuda de IA (Claude)
#include "arduino_controller.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

ArduinoController::ArduinoController() : serial_port(-1), connected(false) {}

ArduinoController::~ArduinoController() {
  if (connected) close(serial_port);
}

bool ArduinoController::connect(const std::string& port) {
  serial_port = open(port.c_str(), O_RDWR | O_NOCTTY);
  if (serial_port < 0) {
    std::cerr << "Error abriendo puerto " << port << std::endl;
    return false;
  }

  termios tty;
  if (tcgetattr(serial_port, &tty) != 0) {
    std::cerr << "Error obteniendo config del puerto" << std::endl;
    return false;
  }

  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);
  tty.c_cflag |= (CLOCAL | CREAD);
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;
  tty.c_lflag = 0;
  tty.c_oflag = 0;
  tty.c_iflag = 0;
  tty.c_cc[VMIN] = 0;  // Non-blocking
  tty.c_cc[VTIME] = 0;

  tcflush(serial_port, TCIFLUSH);
  tcsetattr(serial_port, TCSANOW, &tty);

  connected = true;
  return true;
}

char ArduinoController::readCommand() {
  if (!connected) return '\0';

  char buffer[8];
  int n = read(serial_port, buffer, sizeof(buffer));
  if (n > 0) {
    return buffer[0];
  }
  return '\0';
}