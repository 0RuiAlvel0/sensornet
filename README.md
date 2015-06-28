# sensornet
Open source arduino code designed to operate with comma CMMS API and generate equipment work requests automatically based on actual field conditions

# How do I get this working?

1. Get an arduino controller board <a href="http://store.arduino.cc/product/A000066">from here</a>.
2. Get an arduino ethernet shield (we developed the original code for the wired variant, but please feel free to fork and commit the code for a wireless variant <a href="http://store.arduino.cc/product/A000058">with this hardware</a>).
3. Download the arduino IDE <a href="http://www.arduino.cc/en/Main/Software">here</a>.

The current code was developed for the VERY old arduino duemillenove, and we would love users to edit the code to make it work for the latest versions.

#Create your first comma CMMS work request

***comma CMMS configuration:
1. Register for a free comma CMMS trial account at the <a href="http://commacmms.com">comma CMMS website</a>.
2. Login to comma CMMS and go to "Logged in as..." -> "Modules"-> "API".
3. Click the "+Node" button.
4. Enter "Test node" for node name and "Test node" for node description. Leave all other options as they are (ensure "Set as development node" is checked).
5. Click "Add".

***On the client side:
1. Open your arduino IDE (where you write and download the programs).
2. Copy and paste the code on the "arduino_sensornet.ino" file to a new arduino sketch.
3. 
