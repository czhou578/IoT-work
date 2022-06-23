/*
 * In order for this code to run properly, you must change the wireless
 * access point SSID to your own, as well as change the password.
 * 
 * It is recommended that you change the email and password to your own
 * as well, using the recommended www.smtp2go.com service. Don't forget
 * to change the FROM and TO addresses as well.
 */

// Send Email from Arduino
#include <SoftwareSerial.h>
#define DEBUG true
// connect the TX line from ESP-8266 to Arduino's pin 2
// and the RX line from the ESP-8266 to Arduino's pin 3
SoftwareSerial esp8266(2, 3);
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600);
  Serial.println("Ready !!");
  // reset module
  sendData("AT + RST\r\n", 2000, DEBUG);
  // configures as access point as well as station
  sendData("AT + CWMODE = 3\r\n", 1000, DEBUG);
  // Connect to your access point
  // ***** ENTER YOUR OWN SSID AND PASSWORD *****
  sendData("AT + CWJAP =\"ORBI50\", \"smilingtrumpet202\"\r\n", 5000, DEBUG);
  delay(3000);
  // get ip address
  sendData("AT + CIFSR\r\n", 3000, DEBUG);
  delay(3000);
  // configure for multiple connections
  sendData("AT + CIPMUX = 1\r\n", 2000, DEBUG);
  // turn on server on port 80
  sendData("AT + CIPSERVER = 1, 80\r\n", 1000, DEBUG);
  sendMail();
}

void sendMail()
{
  sendDataln("AT + CIPSTART = 4,\"TCP\",\"mail.smtp2go.com\", 2525", 2000, DEBUG);
  sendDataln("AT+CIPSEND=4,18", 2000, DEBUG);
  // EHLO command
  sendDataln("EHLO 192.168.1.5", 2000, DEBUG);
  sendDataln("AT+CIPSEND=4,12", 2000, DEBUG);
  // AUTH command
  sendDataln("AUTH LOGIN", 2000, DEBUG);
  sendDataln("AT+CIPSEND=4,30", 2000, DEBUG);
  
  // base64 encoded username
  // https://www.base64encode.org/
  // ***** ENTER YOUR OWN USERNAME *****
  // kyle.white@bellevuecollege.edu encoded:
  
  sendDataln("Y29saW4uemhvdUBiZWxsZXZ1ZWNvbGxlZ2UuZWR1", 2000, DEBUG);
  
  // base64 encoded password
  // ***** ENTER YOUR OWN PASSWORD *****
  //IOTPasswordTest12!
  //SU9UUGFzc3dvcmRUZXN0MTIh
  
  sendDataln("AT+CIPSEND=4,14", 2000, DEBUG);
  sendDataln("cG9kaXVtMjE4", 2000, DEBUG);
  sendDataln("AT+CIPSEND=4,35", 2000, DEBUG);
  // MAIL command, from email address
  // ***** UPDATE FOR TESTING FOR OTHER USERS *****
  sendDataln("MAIL FROM:<colin.zhou@bellevuecollege.edu>", 2000, DEBUG);
  sendDataln("AT+CIPSEND=4,33", 2000, DEBUG);
  // RCPT command, to email address
  // ***** UPDATE FOR TESTING FOR OTHER USERS *****
  sendDataln("RCPT TO:<colin.zhou@bellevuecollege.edu>", 2000, DEBUG);
  sendDataln("AT+CIPSEND=4,6", 2000, DEBUG);
  // DATA command
  sendDataln("DATA", 2000, DEBUG);
  sendDataln("AT+CIPSEND=4,20", 2000, DEBUG);
  // Subject
  sendDataln("Subject: Test mail", 2000, DEBUG);
  sendDataln("AT+CIPSEND=4,25", 2000, DEBUG);
  // email body - content
  sendDataln("Test email from Arduino", 2000, DEBUG);
  sendDataln("AT+CIPSEND=4,3", 2000, DEBUG);
  sendDataln(".", 10000, DEBUG);
  sendDataln("AT+CIPSEND=4,6", 2000, DEBUG);
  // QUIT command
  sendDataln("QUIT", 2000, DEBUG);
}

void loop()
{
}

// send data to ESP8266
/*
Params: 
command - data/command to send
timeout - the time to wait for a response
debug - print to Serial window (true = yes, false = no)
Return: 
the response from ESP8266 (if there is a response)
*/
String sendData(String command, const int timeout, boolean debug) 
{
  String response = "";
  // send the read character to the esp8266
  esp8266.print(command);
  long int time = millis();
  while ((time + timeout) > millis())
  {
    while(esp8266.available()) 
    {
      // The esp has daat so display its output to the serial window
      // read the next character
      char c = esp8266.read();
      response += c;
    }
  }
  if(debug)
  {
    Serial.print(response);
  }
  return response;
}

// Send data to ESP8266 using println()
/*
Params: 
timeout - the time to wait for a response
debug - print to Serial window (true = yes, false = no)
Return:
the response from the ESP8266 (if there is a rsponse)
*/
String sendDataln(String command, const int timeout, boolean debug) 
{
  String response = "";
  // send the read character to the ESP8266
  esp8266.println(command);
  long int time = millis();
  while((time + timeout) > millis())
  {
    while(esp8266.available())
    {
      // The esp has data so display to serial window
      // read next character
      char c = esp8266.read();
      response += c;
    }
  }
  if(debug)
  {
    Serial.print(response);
  }
  return response;
}
