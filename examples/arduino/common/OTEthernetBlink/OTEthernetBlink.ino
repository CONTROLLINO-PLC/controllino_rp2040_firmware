/*
  This example polls for sketch updates over Ethernet, sketches
  can be updated by selecting a network port from within
  the Arduino IDE: Tools -> Port -> Network Ports ...

  Circuit:
  * W5100, W5200 or W5500 Ethernet shield attached

  created 13 July 2010
  by dlf (Metodo2 srl)
  modified 31 May 2012
  by Tom Igoe
  modified 16 January 2017
  by Sandeep Mistry
  Ethernet version August 2018
  by Juraj Andrassy

  Modified for Controllino
*/

#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoOTA.h>

 // Enter a MAC address for your controller below.
 // Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Static IP address
IPAddress ip(10, 22, 1, 122);
IPAddress myDns(10, 22, 1, 254);

#define LED_BLINK_INTERVAL 1000 // ms
uint32_t ledtimer = 0;

void setup() {
  //Initialize serial:
  Serial.begin(115200);
  // while (!Serial);
  // delay(2000);

  // LED pin as an output:	
  pinMode(LED_BUILTIN, OUTPUT);

  // start the Ethernet connection:
  Serial.println("Init Ethernet ...");
  Ethernet.begin(mac, ip, myDns);
  Serial.print("IP:");
  Serial.println(Ethernet.localIP());

  // start the OTEthernet library with internal (flash) based storage
  ArduinoOTA.begin(Ethernet.localIP(), "arduino", "password", InternalStorage);

  // init led blink timer
  ledtimer = millis();
}

void loop() {
  // check for updates
  ArduinoOTA.poll();

  // add your normal loop code below ...
  // blink LED
  if (millis() - ledtimer > LED_BLINK_INTERVAL)
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    ledtimer = millis();
  }
}
