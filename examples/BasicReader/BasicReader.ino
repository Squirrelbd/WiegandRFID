#include <WiegandRFID.h>
WiegandRFID rfid;
void setup(){Serial.begin(115200);rfid.begin(18,19);}
void loop(){rfid.loop();if(rfid.available()){RFIDCard c=rfid.read();Serial.println(c.idString);}}
