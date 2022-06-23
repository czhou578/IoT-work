int brightness_1 = 50;
int brightness_2 = 100;
int brightness_3 = 150;

int brightness = 0;

int fadeAmount = 0;
int sensorValue = 0;
int analogInPin = A0; // analog pin
int ledArray[] = {3,5,6,9,10,11};

void setup() {
  Serial.begin(9600);
  pinMode(analogInPin, INPUT);
}

void loop() {
  int ledPin = 0;
  
  sensorValue = analogRead(analogInPin); //read value from specific analog pin
  
  fadeAmount = map(sensorValue, 0, 1023, 0, 255); //map sensor value to range (0,255)
  Serial.print("fadeamount: ");
  Serial.println(fadeAmount);
  
  int len = sizeof(ledArray) / sizeof(int); //calculate length of ledArray
  
  for (ledPin = 1; ledPin < len; ledPin++) {
    brightness = fadeAmount - (2 * ledPin); //assign value to brightness

    Serial.print("brightness: ");
    Serial.println(brightness);
    analogWrite (ledArray[ledPin], brightness); //writes the brightness value to appropriate pin
  }
  
  delay(500);
}





//  Serial.println(brightness);

//  if (brightness <= 0) {
//    fadeAmount = -fadeAmount;
//    brightness = 0;
//  }
//
//  if (brightness >= 255) {
//    fadeAmount = -fadeAmount;
//    brightness = 255;
//  }
