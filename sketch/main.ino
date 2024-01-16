#include "pump.cpp" //enums.h er inkluderet i pump.cpp, derfor burde Status enumen stadig eksisterer.
bool status = true;  //true betyder at der er vand i potteplanten (at de 2 ledninger laver et kredsløb)
long reads = 0; //for at lave et delay mellem at der er kontakt med vandet og ikke er, så en simpel bevægelse på ledningerne ikke får en besked til at blive sendt
bool message_send = true; //sørger for at beskeden ikke bliver spammet, men i stedet kun sendes én gang
unsigned long int time_now = 0;

Pump pump; //pump objektet fra pump.cpp

void setup() {
  Serial.begin(9600);
  pinMode(4, INPUT); //ledninger rør hinanden
  pinMode(2, OUTPUT); //LED
  pinMode(6, OUTPUT); //pump
}


void loop() {
  if (digitalRead(4) == HIGH) {
    reads = 0;
    Serial.println("Potteplanten har vand igen!");
    digitalWrite(2, LOW);
    message_send = false;
  } if (reads > 1000000 && !message_send) {
    sendGET();
    message_send = true;
  } else {
    reads += 1;
  }

  if (millis() >= time_now + 10000) {
      time_now += 10000;
      pump.changeCycle();
  }
}


void sendGET() {
  //hvis ethernet-modulet ville have virket, ville dette have, der hvor beskeden til telefonen ville blive sendt igennem
  digitalWrite(2, HIGH);
  Serial.println("Potteplanten mangler vand!")
}