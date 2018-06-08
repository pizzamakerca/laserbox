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
 * This is the file for Laser Box 0.
 */

#include <SPI.h>
#include <Ethernet.h>
#include <E131.h>

// Change only this value to setup a new laserbox.
#define LASERBOX 0

// Define CONSTANTS
#define UNIVERSE 1
#define RELAY1 2
#define RELAY2 3
#define RELAY3 4
#define RELAY4 5
#define RELAY5 6
#define RELAY6 7
#define RELAY7 8
#define RELAY8 9

// Initialiaze an E131 object.
E131 e131;


void setup() {
    // Configure digital output pins.
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(RELAY3, OUTPUT);
    pinMode(RELAY4, OUTPUT);
    pinMode(RELAY5, OUTPUT);
    pinMode(RELAY6, OUTPUT);
    pinMode(RELAY7, OUTPUT);
    pinMode(RELAY8, OUTPUT);

    // Ensure digital outputs are off (HIGH in the case of relays).
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);

    // Setup the network interface.
    byte macLastByte = LASERBOX;
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0x2F, 0x1E, macLastByte };
    IPAddress dnsAddr(192, 168, 1, 10);
    IPAddress gateway(192, 168, 1, 10);
    IPAddress subnet(255, 255, 255, 0);
    int ipLastOctet = 20 + LASERBOX;
    IPAddress ip(192, 168, 1, ipLastOctet);


    /* Configure from settings above and listen 
     * for Unicast broadcast packets on UDP
     * port 5568.
     */
    e131.begin(mac, ip, subnet, gateway, dnsAddr);
}

void setOutput(int dmx, int value) {
  int channel;
  int level;
  switch (value)
  {
    case 0:
      level = HIGH;
      break;
    case 255:
      level = LOW;
      break;
  }
  
  switch (dmx)
  {
    /* Set each case to map a dmx address sent
     * by the control system to a pin output on
     * the Arduino.  
     * 
     * The firt case in this file will result in
     * dmx address 1 being mapped to RELAY1 (pin 2
     * defined above).
     */
    case ((LASERBOX * 10) + 0):
      channel = RELAY1;
      digitalWrite(channel, level);
      break;
    case ((LASERBOX * 10) + 1):
      channel = RELAY2;
      digitalWrite(channel, level);
      break;
    case ((LASERBOX * 10) + 2):
      channel = RELAY3;
      digitalWrite(channel, level);
      break;
    case ((LASERBOX * 10) + 3):
      channel = RELAY4;
      digitalWrite(channel, level);
      break;
    case ((LASERBOX * 10) + 4):
      channel = RELAY5;
      digitalWrite(channel, level);
      break;
    case ((LASERBOX * 10) + 5):
      channel = RELAY6;
      digitalWrite(channel, level);
      break;
    case ((LASERBOX * 10) + 6):
      channel = RELAY7;
      digitalWrite(channel, level);
      break;
    case ((LASERBOX * 10) + 7):
      channel = RELAY8;
      digitalWrite(channel, level);
      break;
  }
}

void loop() {
  /* Parse a packet */
  if (e131.parsePacket())
  {
    /* Filter the packet down to a specific dmx universe.
     * Skip packets with priority 0 as those packets cause
     * undersirable behavior.
     */
    if (e131.universe == UNIVERSE && e131.packet->priority !=0)
    {
      // Itterate through all 512 dmx addresses looking for values.
      for (int i = 0; i < 511; i++)
      {
        setOutput(i, e131.data[i]);
      }
    }   
  }
}
