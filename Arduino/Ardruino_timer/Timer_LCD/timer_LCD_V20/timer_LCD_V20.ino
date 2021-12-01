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
  while (timeStatus() != timeSet)
  {
    lcd.print("RTC Err");
    delay(2000);
    lcd.clear();
  }
  lcd.print("Build: 10");
  delay(2000);
  if (EEPROM.read(29) == 1)
  {
    Serial.begin(9600);
    Serial.println("Build: 10");
    Serial.println("Date,Time,Current(A),Voltage(V),Mains Current(A),KWH,Grid Time(M),SOG Time Morning(Min),SOG Time Night(Min),Cutoff Amps(A),Cutoff Volts(V),System Volts(V),System DC Amps(A),System AC Amps(A),Grid Supply,AC offset,DC offset,DC Calibrations,AC Calibrations,AC Zero Offset,Timers#,On Time1,Off Time1,On Time2,Off Time2,On Time3,Off Time3,On Time4,Off Time4,On Time5,Off Time5");
  }
}
//*******************************************************
//Main function this will be running in a infinite loop
//*******************************************************
float KWH = 0;
float GridTime = 0;
void loop()
{
  while (1)
  {
    activate_relay();
    Alarm();
  }
}