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
long KWH = 0;
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
    Serial.println("Date,Time,Current(A),Voltage(V),Mains Current(A),KWH,SOG Time Morning(Min),SOG Time Night(Min),Cutoff Amps(A),Cutoff Volts(V),System Volts(V),System Amps(A),Grid Supply,Timers#,On Time1,Off Time1,On Time2,Off Time2,On Time3,Off Time3,On Time4,Off Time4,On Time5,Off Time5");
  }
}
//*******************************************************
//Main function this will be running in a infinite loop
//*******************************************************
void loop()
{
  unsigned int GridTime = 0;
  KWH = 0;
  char cont = 'a';
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();
  while(cont != 'x')
  {
  unsigned long GridTimem = millis();
  activate_relay(GridTime);
  Alarm(GridTime);
  GridTimem = millis()-GridTimem;
    if (GridTimem > 1000)
    {
      GridTimem = GridTimem/60000 ;
      GridTime = GridTime+GridTimem;
      currentMillis=millis();
    }
  }
}







