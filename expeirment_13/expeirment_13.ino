// Intranet Controlled LEDs 

#include <SoftwareSerial.h> 
#define DEBUG true

// make RX Arduino line as pin 2, make TX Arduino line as pin 3
// connect the TX line from the esp to the Arduino's pin 2 
// connect the RX line from the esp to the Arduino's pin 3 

SoftwareSerial esp8266 (2,3); 

void setup() { 
  Serial.begin (9600); 
  // set baudrate for comm with esp8266 
  esp8266.begin (9600); 
  
  // LED1 
  pinMode (11,OUTPUT); 
  digitalWrite (11,LOW); 
  
  // LED2 
  pinMode (12,OUTPUT); 
  digitalWrite (12,LOW); 
  
  // LED3 
  pinMode (13,OUTPUT);
  digitalWrite (13,HIGH); 
  
  sendData ("AT+RST\r\n", 2000, DEBUG); 
  // reset module 
  // configure as access point as well as station 
  sendData ("AT+CWMODE=3\r\n", 1000, DEBUG); 
  // Connects access point please type your own SSID and password 
  sendData("AT+CWJAP=\"UTkorde\", \"XXXXX\"\r\n", 5000, DEBUG); 
  delay (3000); 
  // get ip address 
  sendData ("AT+CIFSR\r\n", 3000, DEBUG); 
  delay (3000); 
  // configure for multiple connections 
  sendData ("AT+CIPMUX=1\r\n", 2000, DEBUG); 
  // turn on server on port 80 
  sendData ("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); 
} 

void loop() {
  
  if (esp8266.available()) {
    // check if the esp is sending a message 
     
    if (esp8266.find ("+IPD,")) { 
      // wait for the serial buffer to fill up (read all serial data) 
      delay (1000); 
      // get the connection id which is used for disconnection 
      // subtract 48 because the read() function returns the ASCII 
      // value and 0 (the first decimal number) starts at 48 
      int connectionId = esp8266.read() - 48; 
      // advance cursor to“pin=” 
      esp8266.find ("pin="); 
      // get first number 
      // if pin 12 then the 1st number is 1, then multiply to get 10 
      int pinNumber = (esp8266.read() - 48) * 10;
      // get second number 
      // if the pin number is 12 then the 2nd number is 2,
      // then add to the first number 
      pinNumber += (esp8266.read() - 48); 
      // toggle pin 
      digitalWrite (pinNumber, !digitalRead (pinNumber)) ; 
      // make close command 
      String closeCommand ="AT+CIPCLOSE="; 
      // append connection id 
      closeCommand += connectionId; 
      closeCommand +="\r\n"; 
      // close connection 
      sendData (closeCommand, 1000, DEBUG); 
    } 
  } 
}

// Sends data to ESP8266 
// Parameters: 
// command - the data/command to send
// timeout - the time to wait for a response 
// debug - print to Serial window? (true = yes, false = no) 
// Returns: The response from the esp8266 (if there is a response) 

String sendData (String command, const int timeout, boolean debug) { 
  String response =""; 
  // send the read character to the esp8266 
  esp8266.print (command); 
  long int time = millis(); 
  while ((time + timeout) > millis()) { 
    while (esp8266.available()) { 
      // The esp has data so display its output to the serial window 
      // read the next character 
      char c = esp8266.read(); 
      response += c;
    }
  }

  if (debug) { 
    Serial.print (response); 
    } 
  return response; 
}
