//hammadiqbal12@gmail.com

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

const char *ssid = "GTother";
const char *password = "GeorgeP@1927";

String val;
int serialvalue = 1;
SoftwareSerial myserial(5,6);

void setup() {
  Serial.begin(115200);
  myserial.begin(38400);
  delay(10);

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
  if(myserial.available()){
      val = myserial.read();
      Serial.println(val);
      serialvalue = val.substring(0,val.indexOf(",")).toInt();
  }
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "143.215.110.89";            //default IP address
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
  url +=  serialvalue;
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
