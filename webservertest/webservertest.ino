#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "wtf";
const char* password = "joost123"; 

AsyncWebServer server(80);

String xData = "1,2,3,4,5"; 
String yData = "10,20,30,40,50"; 

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  Serial.print("ESP32 Web Server's IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) 
  {
    request->send(200, "text/html", "<img src='/graph'>");
  });

  server.on("/graph", HTTP_GET, [](AsyncWebServerRequest* request) 
  {
    String url = "https://quickchart.io/chart?c={type:'line',data:{labels:[" + xData +
                 "],datasets:[{label:'My Data',data:[" + yData + "],borderColor:'blue'}]}}";
    request->redirect(url);
  });

  server.begin();
}

void loop() 
{

}
