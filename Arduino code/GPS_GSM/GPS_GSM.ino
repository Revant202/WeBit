 
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
static const int gpsRX =10, gpsTX =11,gsmRX = 9, gsmTX = 8;
static const uint32_t GPSBaud = 9600;
int  m = 9740;
int y = 71;
TinyGPSPlus gps;
SoftwareSerial ss(gpsRX, gpsTX); 
SoftwareSerial SIM900(gsmRX, gsmTX);
int Buzzer = 13; 
String textForSMS;
int Switch = 12; 

String datareal;
String dataimaginary;  
String combined;
int raw = 1000000;

String datareal2;
String dataimaginary2;
String combined2;

double longitude;
double latitude;

void setup()
{
  SIM900.begin(9600);
  Serial.begin(9600);
  ss.begin(GPSBaud);
  delay(10000); 
  Serial.println(" logging time completed!");
  randomSeed(analogRead(0));
  pinMode(Switch, INPUT);
  digitalWrite(Switch, HIGH);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW);

  Serial.println(F("DeviceExample.ino"));
  Serial.print(F("Testing TinyGPS++ library v. "));
  Serial.println(TinyGPSPlus::libraryVersion());

  Serial.println();
}



void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     
  delay(100);
  SIM900.println("AT + CMGS = \"+918319305246\"");  
  delay(100);
  SIM900.println(message);                         
  delay(100);
  SIM900.println((char)26);                        
  delay(100);
  SIM900.println();
  delay(5000);                                     

}

void loop()
{
  int reading;
  
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
  
  if (digitalRead(Switch) == LOW)
  {
    displayInfo();
    latitude = gps.location.lat(), 6 ;
    longitude = gps.location.lng(), 6 ;
    long datareal = int(latitude);
    int fahad = ( latitude - datareal) * 100000;
    long datareal2 = int(longitude);
    int fahad2 = (longitude - datareal2 ) * 100000;
    textForSMS.concat(fahad);
    //textForSMS = "Longitude:  ";
    textForSMS.concat(datareal2);
    textForSMS = textForSMS + ".";
    textForSMS.concat(fahad2);
    //textForSMS = textForSMS + " Latitude: ";
    textForSMS.concat(datareal);
    textForSMS = textForSMS + ".";
    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent.");
    delay(5000);
  }
  else
    digitalWrite(Switch, HIGH);
  digitalWrite(Buzzer, LOW);
}


void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    Serial.print(" ");
    Serial.print(F("Speed:"));
    Serial.print(gps.speed.kmph());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
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

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
