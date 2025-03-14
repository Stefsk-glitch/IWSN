# Weather station

# Introduction
I'll be building a simple weather station using two ESP32s, which will send the data to eachother using Bluetooth low energie. </br>
A DHT11 sensor will be used to measure temperature and humidity and a LDR to get the light brightness. </br>
There'll also be a basic dashboad that will be hosted by the ESP32 that is inside of the house where the user will be able to view the temperature, humidity and the light brightness until 1 hour ago. </br>

![overview.png](/Img/overview.png) 

# Setting up the ESP32 for Arduino IDE
I've used the following website to setup the ESP32 to use it with the Arduino IDE. </br>
https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

# Testing the ESP32
1. Insert micro-USB to USB into ESP32 and into your computer.
2. Open "ESP32test.ino" with the Arduino IDE after setting up the ESP32 so it can be used with Arduino IDE.
3. Click on select board at the top left of the Arduino IDE.
4. Select the port of the ESP32.
5. Select board "DOIT ESP32 DEVKIT V1".
6. Press on "OK".
7. Click on the upload button at the top left of the Arduino IDE to upload the test code to the ESP32.
8. After the uploading is done press on the Serial Monitor button at the top right of the Arduino IDE.
9. If everything is working correctly the printed texted should be "Hello World!".

# How to wire the DHT11
![wiring.png](/Img/wiring.png) 

# How to test DHT11 
I've used the following website to download the Adafruit library. </br>
https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/

After downloading the Adafruit library open the "DHT11test.ino" file and upload the code to the ESP32. </br>
If everything is working correctly the ESP32 should be printing the statistics of the DHT11 to the serial monitor. </br>

# How to setup a web sever and test it
I've used the following website to setup the web server. </br>
https://www.instructables.com/Implementing-Web-Server-on-ESP32/

After installing the libraries needed to setup the server it's possible to open the "webservertest.ino" file, fill in the credentials and upload it to the ESP32. </br>
If everything is working correctly it should be possible to view the web server by typing the ip address into a browser on the computer that uploaded the code to the ESP32. </br>

# How to test BLE

To test BLE you simply have to flash the "BLEServer.ino" file to an ESP32 and afterwards flash the "BLEClient.ino" file to another ESP32. </br>
If everything is working correctly then the server should get a hello from client message every 5 minutes. </br>

# How is this project as power efficient as possible

To save as much power as possible i'm using BLE and i'm also letting the ESP32 deep sleep for 5 minutes and then send one message just to go back to sleep again to save as much power as possible. </br>

![deepsleeppowerconsumption.png](/Img/deepsleeppowerconsumption.png) 

# How to run the end product

To run the end simply open the main folder and flash the client or server to an ESP32 and afterwards take another ESP32 and flash either the server or client on this one. </br>
Now there is two ESP32s one with the client code and the other with the server code on it. </br>

Look up what ip address the webserver is hosted on. Simply by checking what ip address the rounter gave to it and type it in a webbrowser to see the graphs that the server is filling with measurement values. </br>

The client: </br>
The client works by sending the measurements to the server and going to sleep for 5 minutes to save power. This is the process it keeps repeating. </br>

The server: </br>
The server works by connecting to the network. Afterwards it will start hosting the webserver with the graphs. As last it will boot the BLE server that the client is going to try to make a connection with. </br>
When the BLE server is up it will start advertising so the client is able to find the BLE server and when it gets a connection with the client it will get the measured values from the client and process the values to the webserver so they are visible in the graphs on the webserver. </br>

# Problems faced

1. Boot issue on ESP32 BLE client

This has been fixed by checking if the server that has been found is the right one and if there is a server to connect to. </br>

2. BLE server not getting messages after 1 message has been received

This has been fixed by making an callback on a client leave the server so the server goes back to advertising so it could be found by the client again. </br>

3. Flash memory full because the code was too big

This has been fixed by using NimBLEDevice library instead of the standard one because the standard one is heavier than the NimBLEDevice library is. </br>

4. Watchdog boot looping ESP32

This is fixed by adding a delay of 500 in the loop. </br>