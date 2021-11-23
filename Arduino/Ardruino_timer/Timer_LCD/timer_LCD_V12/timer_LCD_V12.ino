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
  lcd.begin(16, 2);
  lcd.print("Loading");
  pinMode(13, OUTPUT);
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
  if (EEPROM.read(29) == 1)
  {
    Serial.begin(9600);
    Serial.println("Build: 12");
    Serial.println("Date,Time,Current(A),Voltage(V),Mains Current(A),KWH,Grid Time(M),SOG Time Morning(Min),SOG Time Night(Min),Cutoff Amps(A),Cutoff Volts(V),System Volts(V),System DC Amps(A),System AC Amps(A),Grid Supply,AC offset,DC offset,DC Calibrations,AC Calibrations,AC Zero Offset,System Power on Time,Timers#,On Time1,Off Time1,On Time2,Off Time2,On Time3,Off Time3,On Time4,Off Time4,On Time5,Off Time5");
  }
}
//*******************************************************
//Main function this will be running in a infinite loop
//*******************************************************
float KWH = 0;
float GridTime = 0;
unsigned long previousMillis0 = 0;
void loop()
{
  byte PageNo = 1;
  byte NoOfTimers;
  NoOfTimers = EEPROM.read(0);
  float CutOffApms = EEPROM.read(26) / 100;
  CutOffApms = CutOffApms + EEPROM.read(25);
  float CutOffVolts = EEPROM.read(24) / 100;
  CutOffVolts = CutOffVolts + EEPROM.read(23);
  unsigned long SogMorning = EEPROM.read(27);
  SogMorning = SogMorning * 60000;
  unsigned long SogNight =  EEPROM.read(28);
  SogNight = SogNight * 60000;
  previousMillis0 = millis();
  int OnDay = day();
  int OnMonth = month();
  int OnHour = hour();
  int OnMinute = minute();
  while (1)
  {
    PageNo = update_btn(button(), PageNo, 10, 250);
    activate_relay(PageNo, CutOffVolts, CutOffApms, SogMorning, SogNight,OnDay,OnMonth,OnHour,OnMinute);
    Alarm(PageNo, NoOfTimers, CutOffApms,OnDay,OnMonth,OnHour,OnMinute);
    if (GridTime >= 3456000000)
    {
      GridTime = 0;
      previousMillis0 = millis();
      OnDay = day();
      OnMonth = month();
      OnHour = hour();
      OnMinute = minute();
    }
  }
}







