/* DHT library

MIT license
written by Adafruit Industries
*/
#ifndef DHT_H
#define DHT_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


// Uncomment to enable printing out nice debug messages.
//#define DHT_DEBUG

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

// Setup debug printing macros.
#ifdef DHT_DEBUG
  #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
  #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define DEBUG_PRINT(...) {}
  #define DEBUG_PRINTLN(...) {}
#endif

// Define types of sensors.
#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21


class DHT {
  public:
   // Note that count is now ignored as the DHT reading algorithm adjusts itself
   // based on the speed of the processor.
   DHT(uint8_t pin, uint8_t type, uint8_t count) {
     DHT(pin, type);
   };
   DHT(uint8_t pin, uint8_t type);
   void begin(void);
   float readFahrenheit(bool force=false) {
       return readTemperature(true, force);
   };
   float readCelcius(bool force=false) {
       return readTemperature(false, force);
   };
   float readTemperature(bool S=false, bool force=false);
   float convertCtoF(float);
   float convertFtoC(float);
   float computeHeatIndexFahrenheit(float temperature, float percentHumidity) {
       return computeHeatIndex(temperature, percentHumidity, true);
   };
   float computeHeatIndexCelcius(float temperature, float percentHumidity) {
       return computeHeatIndex(temperature, percentHumidity, false);
   };
   float computeHeatIndex(float temperature, float percentHumidity, bool isFahrenheit=true);
   float readHumidity(bool force=false);
   boolean read(bool force=false);

 private:
  uint8_t data[5];
  uint8_t _pin, _type;
  #ifdef __AVR
    // Use direct GPIO access on an 8-bit AVR so keep track of the port and bitmask
    // for the digital pin connected to the DHT.  Other platforms will use digitalRead.
    uint8_t _bit, _port;
  #endif
  uint32_t _lastreadtime, _maxcycles;
  bool _lastresult;

  uint32_t expectPulse(bool level);

  void _init(uint8_t pin, uint8_t type);
};

class InterruptLock {
  public:
   InterruptLock() {
    noInterrupts();
   }
   ~InterruptLock() {
    interrupts();
   }

};

#endif
