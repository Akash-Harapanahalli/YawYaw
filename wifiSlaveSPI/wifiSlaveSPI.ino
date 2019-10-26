//SPI SLAVE (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO 
//CIRCUIT DIGEST

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

volatile boolean received;
volatile byte Slavereceived,Slavesend;
int buttonvalue;
int x;
String val;



void setup()
{
  Serial.begin(115200);

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
  
  pinMode(13,OUTPUT);                 // Setting pin 7 as OUTPUT
  pinMode(MISO,OUTPUT);                   //Sets MISO as OUTPUT (Have to Send data to Master IN 

  SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
  received = false;

  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
  
}
ISR (SPI_STC_vect)                        //Inerrrput routine function 
{
  Slavereceived = SPDR;         // Value received from master if store in variable slavereceived
  received = true;                        //Sets received as True 
}
void loop()
{
   Serial.println("loop beginning");
   if(received)                            //Logic to SET LED ON OR OFF depending upon the value recerived from master
   {
      if (Slavereceived==1) 
      {
        val= "1";         //Sets pin 7 as HIGH LED ON
        Serial.println("Slave LED ON");
      }else
      {
       val = "0";         //Sets pin 7 as LOW LED OFF
        Serial.println("Slave LED OFF");
      }
            
  Slavesend=0;                             
  SPDR = Slavesend;                           //Sends the x value to master via SPDR 
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
  url +=  val;
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
}
