//******************************************************************//
//Board configuration 
//This function is used for configuration various board parameters
//*****************************************************************//
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // LCD Pin interface
void setup() 
{
  pinMode(13, OUTPUT);             
  lcd.begin(16, 2);
  setSyncProvider(RTC.get);
  if (button() == "Left")
  {
    sysconfig();
    setSyncProvider(RTC.get);
  }
  while (timeStatus()!= timeSet)
  {
    lcd.print("RTC Err");
    delay(2000);
    lcd.clear();
  }
  if (EEPROM.read(29) == 1)
  {
    Serial.begin(9600); 
    Serial.println();
    Serial.println("Date,Time,Current(A),Voltage(V),SOG Time Morning(Min),SOG Time Night(Min),Cutoff Amps(A),Cutoff Volts(V),System Volts(V),System Amps(A),Grid Supply,Timers#,On Time1,Off Time1,On Time2,Off Time2,On Time3,Off Time3,On Time4,Off Time4,On Time5,Off Time5");
  }
}
//*******************************************************
//Main function this will be running in a infinite loop 
//*******************************************************
void loop() 
{
  unsigned int GridTime = 0;
  char cont = 'a';
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();
  while(cont != 'x')
  {
  lcd.setCursor(0,1);
  lcd.print("24H TGT(M):");
  lcd.print(GridTime);
  lcd.print("      ");
  unsigned long GridTimem = millis();
  activate_relay();
  Alarm();
  GridTimem = millis()-GridTimem;
  if (GridTimem > 1000)
  {  
  GridTimem = GridTimem/60000 ; 
  GridTime = GridTime+GridTimem;
  currentMillis=millis();
  }
  if ((currentMillis-previousMillis)> 86400000)
  {
    cont = 'x';
  }
  }
}
  
  
  




