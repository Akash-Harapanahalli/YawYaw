//hammadiqbal12@gmail.com

#include <ESP8266WiFi.h>


#define btn0 16
#define btn1 5
#define btn2 4
#define btn3 0


const char *ssid = "GTother";
const char *password = "GeorgeP@1927";


int sensorValue0 = 0;       //sensor value, I'm usingg 0/1 button state
int sensorValue1 = 0;        
int sensorValue2 = 0;        
int sensorValue3 = 0;       

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(btn0, INPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);


  // set the ESP8266 to be a WiFi-client

  Serial.print("Connecting");
  WiFi.mode(WIFI_STA);
  WiFi.begin("GTother", "GeorgeP@1927");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  
  Serial.println("loop beginning");
if(digitalRead(btn0) == LOW) sensorValue0 = 1;
if(digitalRead(btn1) == LOW) sensorValue1 = 1;
if(digitalRead(btn2) == LOW) sensorValue2 = 1;
if(digitalRead(btn3) == LOW) sensorValue3 = 1;

if(digitalRead(btn0) == HIGH) sensorValue0 = 0;
if(digitalRead(btn1) == HIGH) sensorValue1 = 0;
if(digitalRead(btn2) == HIGH) sensorValue2 = 0;
if(digitalRead(btn3) == HIGH) sensorValue3 = 0;


  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "143.215.106.77";            //default IP address
  const int httpPort = 80;
  Serial.println("Client      ");
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  Serial.println("Connected");

  // We now create a URI for the request. Something like /data/?sensor_reading=123
  String url = "/data/";
  url += "?sensor_reading=";
  url +=  sensorValue0;
  Serial.println(url);
  Serial.println("sending    ");
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("sent");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  Serial.println("loop finished");
}
