#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int buzzPin=8,panicPin=3,infraPin=11,gpsTX=5 ,gpsRX=4  ;

TinyGPSPlus gps;
SoftwareSerial loc(gpsRX, gpsTX);
void setup() {
  // put your setup code here, to run once:
pinMode(buzzPin,OUTPUT);
pinMode(panicPin,INPUT);
pinMode(infraPin,INPUT);
Serial.begin(9600);
loc.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
int pressed = digitalRead(panicPin);
int detect = digitalRead(infraPin);
Serial.print(detect);
Serial.println(pressed);
delay(500);


if(detect == 1  || pressed == 0 )
 {digitalWrite(buzzPin,HIGH);}
else
 {digitalWrite(buzzPin,LOW);}

 while (loc.available() > 0)
    if (gps.encode(loc.read()))
      displayInfo();

  if (millis() > 10000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  
  Serial.println();
}
