// Speed Control of DC Motor via Potentiometer 
int potPin = A0;
// PWM pin 
// Pin 5 and 4 to provide voltage to the motor 
int pwmPin = 5; 
int digPin = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("asdasdasda");
  pinMode (pwmPin, OUTPUT); 
  // DC Motor, pwm pin intially set to LOW 
  digitalWrite (pwmPin, LOW); 
  pinMode (digPin, OUTPUT); 
  // DC motor LOW 
  digitalWrite (digPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read POT 1 value 
  int val = analogRead (potPin); 
  // Map the values in the range 0-255 
  int potValue = map (val, 0, 1023, 0, 255);
  Serial.println (potValue); 
  setMotorSpeed (potValue);
}


void setMotorSpeed (int pwmVal) { 
  // writes as per POT 1 value 
  analogWrite (pwmPin, pwmVal); 
  // set to LOW 
  digitalWrite (digPin, LOW);
}
 
