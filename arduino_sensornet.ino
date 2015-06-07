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
char server[] = "prerel.commacmms.com";
char read_key[] = "Enter Read Key Here";
char write_key[] = "Enter Write Key Here";

//you can edit wosummary and/ or wodescription inline on the code below to 
//allow you to send dynamic information from board sensors, hence generating 
//more cler information.
char wosummary[] = {"Enter the text to send as summary"};
char wodescription[] = "Enter the text to send as description";

//****************END API CONFIGURATION****************

//****************OTHER CONFIGURATION****************
//EDIT ONLY IF YOU KNOW WHAT YOU ARE DOING!!!
//See API information for details of what these mean
char request_code[] = "wr_create";
char* wotypes[] = {"P1", "P2", "P3", "P4", "P5"};
char* wopriorities[] = {"cor", "prev", "pred", "break", "oth"};
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
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: prerel.commacmms.com");
    client.println("Connection: close");
    client.println();
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
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
