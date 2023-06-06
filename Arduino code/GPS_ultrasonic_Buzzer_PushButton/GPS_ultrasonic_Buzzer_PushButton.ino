#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int buzzPin=13,panicPin=12,modePin=7, gpsTX=11, gpsRX=10, trigPin = 3, echoPin = 2,pulsePin= A3 ;
int distanceCm,distanceInch,detect,pressed;
long duration;
const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

TinyGPSPlus gps;
SoftwareSerial loc(gpsRX, gpsTX);
void setup() {
  // put your setup code here, to run once:
pinMode(buzzPin,OUTPUT);
pinMode(panicPin,INPUT);
pinMode(modePin,INPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(pulsePin, INPUT);

Serial.begin(9600);
loc.begin(9600);
lcd.begin(16, 2);
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  { lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0, 1);
    lcd.print(gps.location.lng(), 6);
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  TIME "));
  if (gps.time.isValid())
  {
    Serial.print(gps.time.value());
    
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  
  Serial.println();
}
void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//distanceCm = duration*0.034/2;
distanceInch = duration*0.0133/2;

pressed = digitalRead(panicPin);
if(distanceInch > 1)
{detect = 0;}
else
{detect = 1;}
Serial.print(detect);
Serial.println(pressed);
delay(500);


if(detect == 0  || pressed == 0 )
 {digitalWrite(buzzPin,HIGH);
  lcd.setCursor(0, 1);
  if(detect == 0)
   {lcd.print("Device Detached!");}
  else
   {lcd.print("Emergency !");}
 }
else
 {digitalWrite(buzzPin,LOW);
  lcd.clear();}

while (loc.available() > 0)
  if (gps.encode(loc.read()))
     displayInfo();

if (millis() > 10000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
 
}
