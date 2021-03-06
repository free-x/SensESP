#include <Arduino.h>

#include "SoftwareSerial.h"
#include "sensesp_app.h"
#include "wiring_helpers.h"

ReactESP app([]() {
  sensesp_app = new SensESPApp();

#ifndef SERIAL_DEBUG_DISABLED
  SetupSerialDebug(115200);
#endif

  // Software serial port is used for receiving NMEA data
  // ESP8266 pins are specified as DX
  // ESP32 pins are specified as just the X in GPIOX
#ifdef ESP8266
  uint8_t pin = D7;
#elif defined(ESP32)
  uint8_t pin = 4;
#endif
  SoftwareSerial* sw_serial = new SoftwareSerial(pin, -1);
  sw_serial->begin(38400, SWSERIAL_8N1);

  setup_gps(sw_serial);

  sensesp_app->enable();
});
