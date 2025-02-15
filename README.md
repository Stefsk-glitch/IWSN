# Weather station

# Introduction
I'll be building a simple weather station using an ESP32, which will host a web server for viewing the data and send the data to HiveMQ via the MQTT protocol. </br>
A DHT11 sensor will be used to measure temperature and humidity. </br>

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
