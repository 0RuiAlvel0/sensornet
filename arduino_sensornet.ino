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
//See the details page of your node to get the following information:
char server[] = "prerel.commacmms.com";
char read_key[] = "read_key";
char write_key[] = "write_key";
char o[] = "o_id";
char n[] = "node_id";
char output_format[] = "json";
char request_code[] = "wr_create";
char parameters[] = "typ=cor&pri=P3";
//Do not edit the summary of description here. Do it below on the code
//so you can specify the exact problem that ocurred
String sum = "";
String desc = "";
//****************END API CONFIGURATION****************

//****************PHYSICAL CONNECTIONS CONFIGURATION****************
//RESERVED PAUSE Pin
//You should always implement a feature that will let you pause
//the controller so you can do work on equipment without having false
//work requests being generated. As best practices, we will reserve pin 9 of 
//the board for this purpose:
int pausePin = 9;
//variable that will hold the current value of the switch
int Pause = 0;

//DIGITAL SENSORS AREA
//-examples-
//microswitch on pin 11
int switchPin = 8;
//variable that will hold the current value of the switch
int Switch = LOW;

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

float TopLimit0 = 1023;
float BottomLimit0 = 0;

//END ANALOG SENSORS AREA
//****************END PHYSICAL CONNECTIONS CONFIGURATION****************
//*********************************SETUP SYSTEM****************************
void setup() {
  //prepare hardware pause input
  pinMode(pausePin,INPUT);
  
  //prepare digital input
  pinMode(switchPin,INPUT);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. 
  }
  
  Serial.println("comma CMMS sensorNET Project. Initializing...");
  
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to configure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}
//****************************END SETUP SYSTEM******************************

//*****************************LOOP IT!!************************************
void loop(){ 
  //READ PAUSE INPUT
  Pause = digitalRead(pausePin);
  //Read sensor inputs:
  //digital:
  Switch = digitalRead(switchPin);
  //analog:
  LightSensor = analogRead(analogPin);
  delay(5);
  
  if(Pause == LOW){
    Serial.println("In paused state. Not contacting server.");
    Serial.print("Light Sensor(A0): ");
    Serial.println(LightSensor);
    Serial.print("Digital Input(8): ");
    Serial.println(Switch);
    delay(1000);
  }
  else{
    boolean has_trigger = false;
    //Build GET string:
    //customize the summary and description, depending on what error was caught:
    //The error reported to the system will be the last one on the next list (PRIORITY 1):
    //***PRIORITY 2 - on this example the digital switch value is less important than the temperature
    if(Switch == HIGH){
      sum = "&sum=Input%201%20triggered";
      desc = "&desc=Do%20something%20to%20fix%20this%20problem";
      has_trigger = true;
    }
    
    //***PRIORITY 1
    if(LightSensor > TopLimit0){
      sum = "&sum=Reached%20value%20"+String(TopLimit0);
      desc = "&desc=Do%20something%20to%20fix%20this%20problem";
      has_trigger = true;
    }
    else if(LightSensor < TopLimit0){
      //actually we do not want to trigger anyting on low value
    }
    
    //*********************************CONTACT SERVER*******************
    //Contact server with fault details if a fault has been triggered:
    if(has_trigger){
      String query = String("f="+String(output_format)+
      "&o=92&n=10&w="+String(write_key)+"&r="+String(read_key)+
      "&rc="+String(request_code)+"&"+String(parameters)+sum+desc);
      
      client.println("GET /apiengine?"+query+" HTTP/1.1");
    }
    else
      client.println("GET /apiengine? HTTP/1.1");
      
    client.println("Host: "+String(server));
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
      connect_to_server();
      //DO NOT MAKE THE RECONNECT INTERVAL TOO SMALL (60000 is a good number. 3000 for tests).
      Serial.println(".......connecting again in 3s.......");
      delay(3000);
    }
    //*****************************END CONTACT SEVER**********************  
  }
}
//*******************************END LOOP IT!!*******************************

//*******************************OTHER SYSTEM FUCTIONS*******************************
boolean connect_to_server() {
  Serial.println("connecting to comma CMMS server "+String(server));
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
//*******************************OTHER SYSTEM FUCTIONS*******************************
