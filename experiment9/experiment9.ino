/* ESP8266 Setup */
#include <SoftwareSerial.h>
// Connect pin 2 to TX of esp8266,
// connect pin 3 to RX of esp8266
SoftwareSerial mySerial(2,3);

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while(!Serial) 
  {
    ;// wait for serial port to connect
  }
  Serial.println("Perform configuration!");
  // set the data rate for the softwareserial port
  mySerial.begin(9600); // 74880, 57600, 38400, 19200, 9600, 4800
  mySerial.println("Hello, world..");
}

// Loop
void loop() {
  if(mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
  if(Serial.available()) 
  {
    mySerial.write(Serial.read());
  }
}
/*
 * After sketch is uploaded and executed, the following message should appear:
 * Perform Configuration!
 * Hello, world..
 * ERROR
 * 
 * Note the following code:
 * mySerial.begin(115200); // 74880, 57600, 38400, 19200, 9600, 4800
 * 
 * Here the baud rate is set at 115200. This is done as the ESP8266 from the factory is
 * expected to be set at this rate. However, after the sketch is uploaded and executed
 * and if a message is shown that is not matching the previously shown message, then
 * try changing the baud rate and uploading the sketch again. Sometimes changing the rate
 * is needed as it may have been set differently at the factory. Continue to change various
 * rates until you get the correct message.
 * 
 * Next check AT command:
 * Type AT in serial monitor and press "Send" button.
 * OK -> Should be the response in the serial monitor.
 * 
 * Next set baud rate of ESP8266:
 * Type AT+UART=9600,8,1,0,0 and press "Send"
 * This step sets the baud rate to 9600.
 * 
 * Configure ESP8266:
 * Type AT+CWMODE=3 and press "Send" button. Specifying 3 configures the ESP8266 as
 * an AP station and client.
 * 
 * Get list of access points (APs):
 * Type AT+CWLAP and press "Send"
 * The module will return a list of active access points nearby. Identify yours.
 * 
 * Next, connect to an AP:
 * Type AT+CWJAP="Name of your access point","your password" and press "Send"
 * Wait for some time until the module respons with "Wifi Connected"
 * 
 * Find IP of ESP8266:
 * Type AT+CIFSR and press "Send"
 * THe IP address should display.
 * 
 * Check ping:
 * Open a command prompt and ping to the IP that is assigned to the ESP8266. Ping should be
 * successful.
 * 
 */
