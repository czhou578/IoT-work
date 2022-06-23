/*Lab Assignment 17 Chapter 21 Experment
 *CS370 IoT Winter 2022
 *By: Arduino Alphas
 *
 *
 *This Experiment is about monitoring soil moisture 
 *of the area where trees are planted. The soil 
 *moisture is logged to a SD-Card. This helps to 
 *take care of plants using history of soil moisture readings.
 *
 * Include "DS3231-clock_library.zip" to Add .zip Libraries under Sketch tap 
 * 
 *DS3231: Real-Time Clock.
  ** SDA - A4 (UNO ANALOG PINS)
  ** SCL - A5 (UNO ANALOG PINS)
  * 
 * SD Card Pin set:
 ** MOSI - pin 11 (UNO Digital PINS)
 ** MISO - pin 12 (UNO Digital PINS)
 ** CLK - pin 13 (UNO Digital PINS)
 ** CS - pin 10 (UNO Digital PINS)
 * 
 * Moiture Sensor
 ** A0 - A0 (UNO ANALOG PINS) 
*/

#include <Wire.h>
#include <DS3231.h> 
#include <SD.h>
#include <SPI.h>

DS3231 clock;         // module object
RTCDateTime dt;       // Time object
#define SensorPin A0  // define sensro pin

File myFile;          // File object

int pinCS = 10;      // Pin 10 on Ardunio Uno
 
float sensorValue = 0; // Initiate sensor pin

void setup()
{
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);    // set pin mode
  digitalWrite(pinCS, HIGH); // Insure valuse of pin is HIGH so module can initiate
  
  // Waite for Serial port to open
  while(!Serial){
    ;
  }
  
    
  // Initialize DS3231
  Serial.println("Initialize DS3231");
  clock.begin();
  SD.begin();

  // Test if SD card initialized
  if (SD.begin()){
    Serial.println("SD card ready to use.");
  }
  else{
    Serial.println("SD card initialization failed");
    return;
  }
  

  // Atomaticaly (Year, Month, Day, Hour, Minute, Second)
  clock.setDateTime(__DATE__,__TIME__);

}


void loop()
{
  dt = clock.getDateTime();

  // Create a FIle
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the File is opened then put text in File.
  if (myFile){
    Serial.print("Writing to File.....");
  
    // write to File
    //myFile.print("Time:");
    myFile.print(dt.year);    // get the year
    myFile.print("-");
    myFile.print(dt.month);   // get the month
    myFile.print("-");
    myFile.print(dt.day);     // get the day
    myFile.print(",");
    myFile.print(dt.hour);    // get hour
    myFile.print(":");
    myFile.print(dt.minute);  // get min
    myFile.print(":");
    myFile.print(dt.second);  // get sec
  
    myFile.print(",");

    // read a 100 sensor values and get the average to record
    for (int i = 0; i <= 100; i++) { 
      sensorValue = sensorValue + analogRead(SensorPin); 
      delay(1); 
    } 
    //Serial.print(" Soil Moisture: ");
    sensorValue = sensorValue/100.0; 
    myFile.println(int(sensorValue)); 
    
    myFile.close();
  
    Serial.println("Done!");
  }
  // If File does not open print error
  else  {
    Serial.print("Something went wrong!");
  }   
  
  Serial.println();
  delay(1000);

  // Read File to Serial Monitor
  myFile = SD.open("test.txt");
  
  if (myFile){
    Serial.println("Read:");
    
    while(myFile.available()){
      Serial.write(myFile.read());
    }
  myFile.close();
  }
  else {
    Serial.print("Something went wrong!");
  }
}
