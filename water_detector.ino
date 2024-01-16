/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen

 */

#include <SPI.h>
#include <Ethernet.h>
String readString;
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x5F, 0x91 };


char serverName[] = "checkip.dyndns.com"; // myIP server test web page server
EthernetClient client;

//////////////////////

void setup() {
  Serial.begin(9600); 
  Serial.println("connecting to ethernet using DHCP");
  if (Ethernet.begin(mac) == 0) {
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    while(true);
  }


  Serial.println("client readString test 11/04/13"); // so I can keep track of what is loaded
  Serial.println("Send an e in serial monitor to test"); // what to do to test
  Serial.print("IP");
  Serial.println(Ethernet.localIP());
}

void loop(){
  // check for serial input
  if (Serial.available() > 0) //if something in serial buffer
  {
    byte inChar; // sets inChar as a byte
    inChar = Serial.read(); //gets byte from buffer
    if(inChar == 'e') // checks to see byte is an e
    {
      sendGET(); // call sendGET function below when byte is an e
    }
  }  
} 

//////////////////////////

void sendGET() //client function to send/receive GET request data.
{
  if (client.connect(serverName, 80)) {  //starts client connection, checks for connection
    Serial.println("connected");
    client.println("GET / HTTP/1.1"); //download text
    client.println("Host: checkip.dyndns.com");
    client.println("Connection: close");  //close 1.1 persistent connection  
    client.println(); //end of get request
  } 
  else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }

  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
    readString += c; //places captured byte in readString
  }

  //Serial.println();
  client.stop(); //stop client
  Serial.println("client disconnected.");
  Serial.println("Data from server captured in readString:");
  Serial.println();
  Serial.print(readString); //prints readString to serial monitor 
  Serial.println();  
  Serial.println();
  Serial.println("End of readString");
  Serial.println("==================");
  Serial.println();
  readString=""; //clear readString variable

}
