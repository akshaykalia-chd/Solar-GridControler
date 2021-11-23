/******************************************************************
Board configuration
This function is used for configuration various board parameters
*****************************************************************/
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
    Serial.begin(115200);
    Serial.println("Build: 13");
    Serial.println("Date,Time,Current(A),Voltage(V),Mains Current(A),KWH,Grid Time(M),SOG Time Morning(Min),SOG Time Night(Min),Cutoff Amps(A),Cutoff Volts(V),System Volts(V),System DC Amps(A),System AC Amps(A),Grid Supply,AC offset,DC offset,DC Calibrations,AC Calibrations,AC Zero Offset,System Power on Time,Timers#,On Time1,Off Time1,On Time2,Off Time2,On Time3,Off Time3,On Time4,Off Time4,On Time5,Off Time5");
  }
}
/*******************************************************
Main function this will be running in a infinite loop
*******************************************************/
void loop()
{
  float KWH = 0;
  float GridTime = 0;
  float volts = 0;
  float amps = 0;
  float ampsac = 0;
  byte PageNo = 1;
  byte NoOfTimers;
  NoOfTimers = EEPROM.read(0);
  float CutOffApms = EEPROM.read(26) / 100.00;
  CutOffApms = CutOffApms + EEPROM.read(25);
  float CutOffVolts = EEPROM.read(24) / 100.00;
  CutOffVolts = CutOffVolts + EEPROM.read(23);
  unsigned long SogMorning = EEPROM.read(27);
  SogMorning = SogMorning * 60000;
  unsigned long SogNight =  EEPROM.read(28);
  SogNight = SogNight * 60000;
  float sysvoltsdc = EEPROM.read(21) / 1024.00;
  int OnDay = day();
  int OnMonth = month();
  int OnHour = hour();
  int OnMinute = minute();
  int onTime[5];
  int offTime[5];
  for (int i = 0; i < NoOfTimers; i++)
  {
    onTime[i] = get_timer(i, NoOfTimers, "OnTime");
    offTime[i] = get_timer(i, NoOfTimers, "OffTime");
  }
  float SysampsDC = EEPROM.read(22) / 1024.00;
  float DCcalf = EEPROM.read(40) / 100.00;
  DCcalf = DCcalf + EEPROM.read(39);
  int DcOffset = get_offset("DC");
  float SysampsAC = EEPROM.read(30) / 1024.00;
  float ACcalf = EEPROM.read(42) / 100.00;
  ACcalf = ACcalf + EEPROM.read(41);
  int ACOffset = get_offset("AC");
  byte ACerror = EEPROM.read(43);
  byte RelayOn = 0;
  digitalWrite(13, LOW);
  byte RunCount = 0;
  unsigned long elaptime = 0;
  unsigned long previousMillis = millis ();
  while (1)
  {
    PageNo = update_btn(button(), PageNo, 10, 1);
    RunCount++;
    if (RunCount > 100)
    {
      RunCount = 0;
    }
    volts = avg_voltage(sysvoltsdc);
    PageNo = update_btn(button(), PageNo, 10, 1);
    amps = avg_currentDc(SysampsDC, DCcalf, DcOffset);
    PageNo = update_btn(button(), PageNo, 10, 1);
    ampsac = avg_currentAc(SysampsAC, ACcalf, ACOffset, ACerror);
    PageNo = update_btn(button(), PageNo, 10, 1);
    for (int i = 0; i < NoOfTimers; i++)
    {
      RelayOn = activate_relay(volts, CutOffVolts, RelayOn, onTime[i], offTime[i]);
      PageNo = update_btn(button(), PageNo, 10, 1);
      if (RunCount == 100)
      {
        RelayOn = deactivate_relay(amps, CutOffApms, SogMorning, SogNight, RelayOn, elaptime, offTime[i]);
      }
    }
    if (RelayOn == 0)
    {
      elaptime = 0;
    }
    GridTime = GridTime + Cal_Gridtime(amps, previousMillis);
    KWH = KWH + Cal_KWH(amps, previousMillis, ampsac);
    previousMillis = millis();
    PageNo = update_btn(button(), PageNo, 10, 1);
    lcd_Display(RelayOn, amps, volts, ampsac, PageNo, OnDay, OnMonth, OnHour, OnMinute, KWH, GridTime, CutOffVolts, CutOffApms, SogMorning, SogNight, sysvoltsdc, SysampsDC, SysampsAC);
    datalog(RelayOn, amps, volts, ampsac, OnDay, OnMonth, OnHour, OnMinute, KWH, GridTime, CutOffVolts, CutOffApms, SogMorning, SogNight, sysvoltsdc, SysampsDC, SysampsAC, NoOfTimers, ACOffset, DcOffset, ACcalf, DCcalf, ACerror, onTime[0], offTime[0], onTime[1], offTime[1], onTime[2], offTime[2], onTime[3], offTime[3], onTime[4], offTime[4]);
    if (GridTime > 4294966296)
    {
      GridTime = 0;
    }
    if (KWH > 4294966296)
    {
      KWH = 0;
    }
    if (RelayOn != 0)
    {
      elaptime = elaptime + millis() - elaptime;
    }
  }
}










