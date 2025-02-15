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

# How to wire the DHT11
![wiring.png](/Img/wiring.png) 

# How to test DHT11 
I've used the following website to download the Adafruit library. </br>
https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/

After downloading the Adafruit library open the "DHT11test.ino" file and upload the code to the ESP32. </br>
If everything is working correctly the ESP32 should be printing the statistics of the DHT11 to the serial monitor. </br>

# How to setup the HiveMQ broker and test it
I've followed the following website to setup the broker and understand how to send messages to the broker. </br>
https://medium.com/engineering-iot/connecting-esp32-to-hivemq-for-real-time-iot-data-streaming-with-mqtt-8813f48cb1a4

After setting up the broker, installing the pubsubclient library open "MQTTtest.ino" file, fill in the credentials and upload the code to the ESP32. </br>
If everything is working correctly the ESP32 should be sending a message to the topic "/test". </br>
This should be visible in the HiveMQ web client by subscribing to the topic "/test". </br> 

# How to setup a web sever and test it
I've used the following website to setup the web server. </br>
https://www.instructables.com/Implementing-Web-Server-on-ESP32/

After installing the libraries needed to setup the server it's possible to open the "webservertest.ino" file, fill in the credentials and upload it to the ESP32. </br>
If everything is working correctly it should be possible to view the web server by typing the ip address into a browser on the computer that uploaded the code to the ESP32. </br>