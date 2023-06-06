# include "LiquidCrystal.h"  //lcd libary                                       
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);   //LCD object Parameters: (rs, enable, d4, d5, d6, d7)
float IRpin = A0;                                                                                                         
void setup() {      // setup perameter
lcd.begin(16,2);                                                   

}

void loop()
{   
  
  float volts = analogRead(IRpin)*0.0048828125;   
  float distance = 65*pow(volts, -1.10); 
  lcd.setCursor(1,1);      
  //delay(1000);

 float  sensorValue = analogRead(IRpin);
 lcd.setCursor(1,2);
 lcd.print(distance);
 if(distance > 50)
 {
   //lcd.print(distance); 
   lcd.print("     ALERT    ");
 }
 else
 {
    //lcd.print(distance); 
    lcd.print("  No Alert");
 }
 delay(650);

}
