/*
Parafernalia Lda, Macau SAR, June 2015
comma CMMS web client for interaction with the comma CMMS API.

Notes:
1. Connections and board configuration routines, from the standard arduino example code for ethernet connections.
2. Fully open-source code
3. Project page available at https://github.com/commacmms/sensornet
 */

#include <SPI.h>
#include <Ethernet.h>

//****************NETWORK HARDWARE SETTINGS****************
// Enter a MAC address for your controller below in case you need to.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet client library
EthernetClient client;

//****************END NETWORK HARDWARE SETTINGS************

//****************API CONFIGURATION****************
//Enter your comma CMMS server address
//Free accounts are currently located on:
//http://prerel.commacmms.com
//http://prerel1.commacmms.com
//http://prerel2.commacmms.com
char server[] = "f001.commacmms.com";
char read_key[] = "Enter Read Key Here";
char write_key[] = "Enter Write Key Here";

//you can edit wosummary and/ or wodescription inline on the code below to 
//allow you to send dynamic information from board sensors, hence generating 
//more cler information.
char wosummary[] = "Enter the text to send as summary";
char wodescription[] = "Enter the text to send as description";
//****************END API CONFIGURATION****************

//****************PHYSICAL CONNECTIONS CONFIGURATION****************
//RESERVED PAUSE Pin
//You should always implement a feature that will let you pause
//the controller so you can do work on equipment without having false
//wor requests being generated. As best practices, we will reserve pin 12 of 
//the board for this purpose:
int pausePin = 12;

//DIGITAL SENSORS AREA
//-examples-
//microswitch on pin 11
int switchPin = 11;
//Select trigger condition
//for each digital sensor always use TriggerHigh_<pin number> = true, false;
int TriggerHigh_11 = false;

//END DIGITAL SENSORS AREA
//ANALOG SENSORS AREA
//-examples-
//light sensor connected on A0:
int analogPin = 0;
//variable that will hold the sensor value on A0:
int LightSensor = 0;
//Select trigger condition
//For each analog sensor, set
//TopLimit<pin_number>
//BottomLimit<pin_number>

float TopLimit0 = 200;
float BottomLimit0 = 100;

//END ANALOG SENSORS AREA
//****************END PHYSICAL CONNECTIONS CONFIGURATION****************

//****************OTHER CONFIGURATION****************
//EDIT ONLY IF YOU KNOW WHAT YOU ARE DOING!!!
//See API information for details of what these mean
char request_code[] = "wr_create";
char* wotypes[] = {"P1", "P2", "P3", "P4", "P5"};
char* wopriorities[] = {"cor", "prev", "pred", "break", "oth"};
char get_string[] = "";
//****************END OTHER CONFIGURATION****************

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. 
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to configure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  //This has no need to be a fast process. Set a refresh interval of
  //10 seconds between value samples:
  delay(10000);
  
  //Read sensor inputs:
  
  //Determine if values are above limits:
  
  //Prepare GET string:
  
  //Contact server with fault details:
  client.println("GET /apiengine? HTTP/1.1");
  client.println("Host: f001.commacmms.com");
  client.println("Connection: close");
  client.println();
  
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}
