int brightness = 0;
int fadeAmount = 0;
int sensorValue = 0;
int analogInPin = A0;
int ledArray[] = {3,5,6,9,10,11};

void setup() {
  Serial.begin(9600);
//  sensorValue = analogRead(analogInPin);
//  fadeAmount = map(sensorValue, 0, 1023, 0, 255); //map 0 to range (0,255)
  Serial.print("FadeAmount is:");
  Serial.println(fadeAmount);
}

void loop() {
  int ledPin = 0;
  sensorValue = analogRead(analogInPin);
  fadeAmount = map(sensorValue, 0, 1023, 0, 255); //map 0 to range (0,255)
  brightness = fadeAmount;

  int len = sizeof(ledArray) / sizeof(int);
  for (ledPin = 0; ledPin < len; ledPin++) {
    analogWrite (ledArray[ ledPin ], brightness);
  }

  Serial.println(brightness);

//  if (brightness <= 0) {
//    fadeAmount = -fadeAmount;
//    brightness = 0;
//  }
//
//  if (brightness >= 255) {
//    fadeAmount = -fadeAmount;
//    brightness = 255;
//  }

  delay(500);
}
