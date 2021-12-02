//*******************************************************
//Functions to setup timers
//EPROM Range 0 to 10
//EPROM addr 0 = TimerNos
//EPROM Range 1 to 10 for OnHour and OnMin
//EPROM Range 11 to 20 for OffHour and OffMin
//*******************************************************
void setup_timers()
{
  byte TimerNos = EEPROM.read(0);
  TimerNos = update_Tcom("TimerNos", TimerNos, 6);
  EEPROM.update(0, TimerNos);
  byte TimerComp = 0;
  for (byte i = 0; i < TimerNos; i++)
  {
    byte addr = i + 1;
    byte addr1 = addr + TimerNos;
    byte addr2 = addr1 + TimerNos;
    byte addr3 = addr2 + TimerNos;
    TimerComp = update_timer(i + 1, 24, EEPROM.read(addr), "On Hour");
    EEPROM.update(addr, TimerComp);
    delay(250);
    TimerComp = update_timer(i + 1, 60, EEPROM.read(addr1), "On Minute");
    EEPROM.update(addr1, TimerComp);
    delay(250);
    TimerComp = update_timer(i + 1, 24, EEPROM.read(addr2), "Off Hour");
    EEPROM.update(addr2, TimerComp);
    delay(250);
    TimerComp = update_timer(i + 1, 60, EEPROM.read(addr3), "Off Minute");
    EEPROM.update(addr3, TimerComp);
  }
}

byte update_timer(byte TimerNo, byte TimerValueMax, byte TimerValue, String TimerCom)
{
  lcd.setCursor(0, 1);
  lcd.print("Timer ");
  lcd.print(TimerNo);
  lcd.print("         ");
  TimerValue = update_Tcom(TimerCom, TimerValue, TimerValueMax);
  return TimerValue;
}

//*******************************************************
//Function to get Ontime and OffTime for timers
//Do not modify unless explicitly defined by a comment
//*******************************************************
int get_timer(int timerNo, byte NoOfTimers, String sel)
{
  byte addr = timerNo + 1;
  byte addr1 = addr + NoOfTimers;
  byte addr2 = addr1 + NoOfTimers;
  byte addr3 = addr2 + NoOfTimers;
  if (sel == "OnTime")
  {
    int OnTime = EEPROM.read(addr); //OnHours
    OnTime = OnTime * 100;
    OnTime = OnTime + EEPROM.read(addr1); // On Mins
    return OnTime;
  }
  if (sel == "OffTime")
  {
    int OffTime = EEPROM.read(addr2); // Off Hours
    OffTime = OffTime * 100;
    OffTime = OffTime + EEPROM.read(addr3); // Off Mins
    return OffTime;
  }
}


