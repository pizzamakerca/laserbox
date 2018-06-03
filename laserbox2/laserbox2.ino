/*
* Ethernet_Test.ino - Simple sketch to listen for E1.31 data on an 
*                     UNO Ethernet shield and print some statistics.
*
* Project: E131 - E.131 (sACN) library for Arduino
* Copyright (c) 2015 Shelby Merrick
* http://www.forkineye.com
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*/

/*
 * This is the file for Laser Box 2
 */

#include <SPI.h>
#include <Ethernet.h>
#include <E131.h>

#define UNIVERSE 1
#define RELAY1 2
#define RELAY2 3
#define RELAY3 4
#define RELAY4 5
#define RELAY5 6
#define RELAY6 7
#define RELAY7 8
#define RELAY8 9

// Increment the value "0x00" to setup a new unit.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0x2F, 0x1E, 0x01 };
IPAddress dnsAddr(192, 168, 1, 10);
IPAddress gateway(192, 168, 1, 10);
IPAddress subnet(255, 255, 255, 0);
// Increment the value "20" to setup a new unit.
IPAddress ip(192, 168, 1, 21);

E131 e131;



void setup() {
    // Setup Pins
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(RELAY3, OUTPUT);
    pinMode(RELAY4, OUTPUT);
    pinMode(RELAY5, OUTPUT);
    pinMode(RELAY6, OUTPUT);
    pinMode(RELAY7, OUTPUT);
    pinMode(RELAY8, OUTPUT);

    // Set outputs off
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    

    /* Configure via DHCP and listen Unicast on the default port */
    e131.begin(mac, ip, subnet, gateway, dnsAddr);
}

void setOutput(int dmx, int value) {
  int channel;
  switch (dmx)
  {
    // Set each case to correspond to the dmx address.
    // Remember the offset is the dmx channel - 1.
    case 19:
      channel = RELAY1;
      break;
    case 20:
      channel = RELAY2;
      break;
    case 21:
      channel = RELAY3;
      break;
    case 22:
      channel = RELAY4;
      break;
    case 23:
      channel = RELAY5;
      break;
    case 24:
      channel = RELAY6;
      break;
    case 25:
      channel = RELAY7;
      break;
    case 26:
      channel = RELAY8;
      break;
    default:
      channel = RELAY1;
      break;
  }

  int level;
  switch (value)
  {
    case 0:
      level = HIGH;
      break;
    case 255:
      level = LOW;
      break;
    default:
      level = HIGH;
      break;
  }
  
  digitalWrite(channel, level);
}

void loop() {
  /* Parse a packet */
  if (e131.parsePacket())
  {
    if (e131.universe == UNIVERSE && e131.packet->priority !=0)
    {
      for (int i = 19; i < 27; i++)
      {
        setOutput(i, e131.data[i]);
      }
    }   
  }
}
