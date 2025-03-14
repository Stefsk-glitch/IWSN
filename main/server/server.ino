#include <NimBLEDevice.h>
#include <NimBLEUtils.h>
#include <NimBLEServer.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <vector>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

const char* ssid = "xxx";
const char* password = "xxx"; 

AsyncWebServer server(80);
NimBLEServer *pServer;
NimBLEAdvertising *pAdvertising;

std::vector<int> yData1;
std::vector<int> yData2;
std::vector<int> labels;

const int MAX_DATA_POINTS = 50;

int dataCounter = 0;

class MyServerCallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) override {
        Serial.println("Client connected.");
    }

    void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override {
        Serial.println("Client disconnected. Restarting advertising...");
        NimBLEDevice::startAdvertising();
    }
};

class MyCallbacks : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
        Serial.println("Data received from client:");
        std::string value = pCharacteristic->getValue();

        if (value.empty()) {
            Serial.println("Warning: Received empty message!");
        } else {      
            String receivedData = String(value.c_str());

            int delimiterIndex = receivedData.indexOf(' ');
            if (delimiterIndex != -1) {
              int hum = receivedData.substring(0, delimiterIndex).toInt();
              int temp = receivedData.substring(delimiterIndex + 1).toInt();

              if (yData1.size() >= MAX_DATA_POINTS) {
                yData1.erase(yData1.begin());  
                yData2.erase(yData2.begin());
                labels.erase(labels.begin());
              }

              yData1.push_back(hum);
              yData2.push_back(temp);
              labels.push_back(++dataCounter); 

              Serial.println("Humidity: " + String(hum));
              Serial.println("Temperature: " + String(temp));
            }
        }
    }
};

String vectorToString(const std::vector<int>& data) {
  String result = "";
  for (size_t i = 0; i < data.size(); i++) {
    result += String(data[i]);
    if (i != data.size() - 1) {
      result += ",";
    }
  }
  return result;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE Server...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("ESP32 Web Server IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", "<h1>Weather station</h1>"
                                    "<img src='/graph'><br><br>"
                                    "<img src='/graph2'>");
  });

  server.on("/graph", HTTP_GET, [](AsyncWebServerRequest* request) {
    String url = "https://quickchart.io/chart?c={type:'line',data:{labels:[" + vectorToString(labels) + "],datasets:[{label:'Humidity',data:[" + vectorToString(yData1) + "],borderColor:'blue'}]}}";
    //Serial.println(url);
    request->redirect(url);
  });

  server.on("/graph2", HTTP_GET, [](AsyncWebServerRequest* request) {
    String url = "https://quickchart.io/chart?c={type:'line',data:{labels:[" + vectorToString(labels) + "],datasets:[{label:'Temperature',data:[" + vectorToString(yData2) + "],borderColor:'yellow'}]}}";
    //Serial.println(url);
    request->redirect(url);
  });

  server.begin();

  NimBLEDevice::init("ESP32_BLE_Server");

  pServer = NimBLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  NimBLEService *pService = pServer->createService(SERVICE_UUID);
  NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY
  );

  pCharacteristic->setValue("Hello from server");
  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  Serial.println("Server ready. Waiting for connections...");
}

void loop() 
{
    delay(500);  // Prevent watchdog resets
}