//SPI MASTER (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO
//CIRCUIT DIGEST

#include<SPI.h>                             //Library for SPI   
void setup ()
{
  Serial.begin(115200);                   //Starts Serial Communication at Baud Rate 115200
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(SS, HIGH);                 // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)
  pinMode(13,OUTPUT);
}

void loop()
{
  byte Mastersend, Mastereceive;
  digitalWrite(SS, LOW);                  //Starts communication with Slave connected to master

  Mastersend = 1;
  Mastereceive = SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave

  digitalWrite(SS, HIGH);
  digitalWrite(13, HIGH);             //Sets pin 7 HIGH
  Serial.println("Master LED ON");
  delay(2000);
  digitalWrite(SS, LOW);
  Mastersend = 0;
  Mastereceive = SPI.transfer(Mastersend);
  digitalWrite(SS, HIGH);

  digitalWrite(13, LOW);              //Sets pin 7 LOW
  Serial.println("Master LED OFF");
  delay(2000);
}
