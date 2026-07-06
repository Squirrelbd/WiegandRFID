#include "WiegandRFID.h"
volatile uint32_t WiegandRFID::raw=0;
volatile uint8_t WiegandRFID::bits=0;
volatile uint32_t WiegandRFID::lastPulse=0;
uint8_t WiegandRFID::_d0; uint8_t WiegandRFID::_d1;
void IRAM_ATTR WiegandRFID::isr0(){raw<<=1;bits++;lastPulse=millis();}
void IRAM_ATTR WiegandRFID::isr1(){raw=(raw<<1)|1;bits++;lastPulse=millis();}
void WiegandRFID::begin(uint8_t d0,uint8_t d1){_d0=d0;_d1=d1;pinMode(d0,INPUT_PULLUP);pinMode(d1,INPUT_PULLUP);attachInterrupt(digitalPinToInterrupt(d0),isr0,FALLING);attachInterrupt(digitalPinToInterrupt(d1),isr1,FALLING);}
void WiegandRFID::loop(){
 if(bits==26 && millis()-lastPulse>timeoutMs){
   uint32_t r=raw; raw=0; bits=0;
   uint8_t f=(r>>17)&0xFF; uint16_t c=(r>>1)&0xFFFF;
   uint32_t id=((uint32_t)f<<16)|c;
   if(id==lastID && millis()-lastRead<dupMs) return;
   lastID=id; lastRead=millis();
   card.bitLength=26; card.facilityCode=f; card.cardNumber=c; card.cardID=id; card.rawData=r;
   snprintf(card.idString,sizeof(card.idString),"%010lu",(unsigned long)id);
   ready=true;
 }
}
bool WiegandRFID::available(){return ready;}
RFIDCard WiegandRFID::read(){ready=false;return card;}
