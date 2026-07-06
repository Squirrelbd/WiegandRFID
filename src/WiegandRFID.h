#ifndef WIEGAND_RFID_H
#define WIEGAND_RFID_H
#include <Arduino.h>
struct RFIDCard{
  uint8_t bitLength=0;
  uint8_t facilityCode=0;
  uint16_t cardNumber=0;
  uint32_t cardID=0;
  uint32_t rawData=0;
  char idString[11];
};
class WiegandRFID{
public:
  void begin(uint8_t d0,uint8_t d1);
  void loop();
  bool available();
  RFIDCard read();
  void setDuplicateTime(uint32_t ms){dupMs=ms;}
  void setReadTimeout(uint32_t ms){timeoutMs=ms;}
private:
  static void IRAM_ATTR isr0();
  static void IRAM_ATTR isr1();
  static volatile uint32_t raw;
  static volatile uint8_t bits;
  static volatile uint32_t lastPulse;
  static uint8_t _d0,_d1;
  RFIDCard card;
  bool ready=false;
  uint32_t lastID=0,lastRead=0,dupMs=1000,timeoutMs=25;
};
#endif