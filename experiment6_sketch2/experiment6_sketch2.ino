//#include "ledStruct.h"
#include <EEPROM.h>

struct LEDData { 
  int ledno; 
//  char name[8];
  char name[6];
};


int addr = 0;
const int delay_dur = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int ledPin = 2; ledPin <= 7; ledPin++) { //was 9
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
  }
}

void make_LEDsOff() {
  for (int ledPin = 2; ledPin <= 7; ledPin++) { //was 9
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
  }  
}

void loop() {
  // put your main code here, to run repeatedly:
  LEDData ledData;

  int i = addr / sizeof(struct LEDData);
  EEPROM.get(addr, ledData);
  Serial.print(ledData.ledno);

  Serial.print ("\t"); 
  Serial.println (ledData.name); 
  
  if (i == 0) { 
    make_LEDsOff(); delay (delay_dur); 
  } else { // glow LEDs one by one  
    digitalWrite (ledData.ledno + 1, LOW); //add 1 to get pin 2 to 9
    delay (delay_dur); 
  }

  // increment the address by the size of structure LEDData 
  addr = addr + sizeof (struct LEDData); 
  if (addr > (6 * sizeof (struct LEDData))) { //was 8
    // restart after addr is above 8 objects 
    addr = 0;
  }

}
