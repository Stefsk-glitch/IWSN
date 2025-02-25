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

# TODO

# How to test BLE

To test BLE you simply have to flash the BLEServer to an ESP32 and afterwards flash another ESP32 with BLEClient. </br>
If everything is working correctly then the server should get a hello from client message every 5 minutes. </br>

# How is this project as power efficient as possible

To save as much power as possible i'm using BLE and i'm also letting the ESP32 deep sleep for 5 minutes and then send one message just to go back to sleep again to save as much power as possible. </br>

![deepsleeppowerconsumption.png](/Img/deepsleeppowerconsumption.png) 

# How to run the end product

TODO </br>

# Problems faced

1. Boot issue on ESP32 BLE client

This has been fixed by checking if the server that has been found is the right one and if there is a server to connect to. </br>

2. BLE server not getting messages after 1 message has been received

This has been fixed by making an callback on a client leave the server so the server goes back to advertising so it could be found by the client again. </br>