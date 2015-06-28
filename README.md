# What is the sensorNET project?
Open source arduino code designed to operate with comma CMMS API and generate equipment work requests automatically based on actual field conditions

# How do I get this working?

1. Get an arduino controller board [from here](http://store.arduino.cc/product/A000066).
2. Get an arduino ethernet shield (we developed the original code for the wired variant, but please feel free to fork and commit the code for a wireless variant [with this hardware](http://store.arduino.cc/product/A000058)).
3. Download the arduino IDE [here](http://www.arduino.cc/en/Main/Software).

The current code was developed for the VERY old arduino duemillenove, and we would love users to edit the code to make it work for the latest versions.

#Configuration Steps

##comma CMMS configuration: 

Step 1: Register for a free comma CMMS trial account at the <a href="http://commacmms.com">comma CMMS website</a>.

Step 2: Login to comma CMMS and go to "Logged in as..." -> "Modules"-> "API".

Step 3: Click the "+Node" button.

Step 4:Enter "Test node" for node name and "Test node" for node description. Leave all other options as they are 
(ensure "Set as development node" is checked).

Step 5: Click "Add".

##Cient side hardware setup:
Step 1: plug your ethernet shield on top of your arduino controller board

Step 2: plug in your ethernet shield to an ethernet cable with internet access.

Step 3: connect the circuit specified on the following picture (or simlar):
![arduino example circuit](http://googledrive.com/host/0B-a-9_EzFNVnQ0tBd1QxeVhTLWM/actual.jpg)

The implementation of the circuit above:
![arduino example circuit actual](http://googledrive.com/host/<folderID>/<filename>)

Step 4: connect your arduino to your computer

##Client side software configuration:
Step 1: Open your arduino IDE (where you write and download the programs).

Step 2: Copy and paste the code on the "arduino_sensornet.ino" file to a new arduino sketch.

Step 3: Look at the Request string text which will be something like the following:
http://server_name/apiengine?f=output_format&o=number_1&n=number_2&w=write_key&r=read_key&rc=request_code&parameters

take the values above and place them on the following variables:

char server[] = "server_name";

char read_key[] = "read_key";

char write_key[] = "write_key";

char o[] = "number_1";

char n[] = "number_2";

Leave all other variables as they are. 

##Final steps
Step 1: load the arduino code to the board

Step 2: Connect your serial monitor

Step 3: If all went well, you should see system messages.
