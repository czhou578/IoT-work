
#include <EEPROM.h>

struct LEDData { 
  int ledno; 
//  char name[8];
  char name[6];
};

int addr = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  put_to_EEPROM();
}

void put_to_EEPROM() {
  LEDData data[7] = { //was 9
    {0, "OFF"}, 
    {1, "LED-1"}, 
    {2, "LED-2"}, 
    {3, "LED-3"}, 
    {4, "LED-4"},
    {5, "LED-5"}, 
    {6, "LED-6"}, 
//    {7, "LED-7"}, 
//    {8, "LED-8"}
  };

  int address = 0; 
  for (int i = 0; i <= 6; i++) { //was 8, writes data at 0, 1, 2…8 EEPROM.put (address, data[i]); 

    address = address + sizeof (struct LEDData); // write after sizeof struct 
    delay (100); 
  } 
}  



void loop() {
  // put your main code here, to run repeatedly:
  
}
