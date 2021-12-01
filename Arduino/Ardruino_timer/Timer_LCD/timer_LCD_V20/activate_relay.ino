//*******************************************************
//Function to activate relay
//Do not modify unless explicitly defined by a comment
//*******************************************************
void activate_relay(byte PageNo,float CutOffVolts,float CutOffApms,unsigned long SogMorning,unsigned long SogNight,int OnDay, int OnMonth, int OnHour, int OnMinute)
{
  unsigned long previousMillis = millis();
  float volts = avg_voltage();
  float amps = avg_current("DC");
  float ampsac = avg_current("AC");
  float mamps = 0;
  digitalWrite(13, LOW);
  boolean RelayOn = false;
  lcd_Display(amps, volts, "Off", ampsac,PageNo,OnDay, OnMonth, OnHour, OnMinute);
  datalog("Off", amps, ampsac, volts,OnDay, OnMonth, OnHour, OnMinute);
  if (volts < CutOffVolts)
  {
    digitalWrite(13, HIGH);
    RelayOn = true;
    while (millis() - previousMillis < 30000)
    {
      volts = avg_voltage();
      amps = avg_current("DC");
      ampsac = avg_current("AC");
      lcd_Display(amps, volts, "On", ampsac,PageNo,OnDay, OnMonth, OnHour, OnMinute);
      datalog("On", amps, ampsac, volts,OnDay, OnMonth, OnHour, OnMinute);
      mamps = amps * (-1); //Moded amps
    }
    while (RelayOn == true)
    {
      lcd_Display(amps, volts, "On", ampsac,PageNo,OnDay, OnMonth, OnHour, OnMinute);
      datalog("On", amps, ampsac, volts,OnDay, OnMonth, OnHour, OnMinute);
      volts = avg_voltage();
      amps = avg_current("DC");
      ampsac = avg_current("AC");
      float mamps = amps * (-1); //moded amps
      if (mamps < CutOffApms)
      {
        digitalWrite(13, LOW);
        RelayOn = false;
      }
      if (hour() >= 07 && hour() <= 16)
      {
        if (millis() - previousMillis > SogMorning)
        {
          digitalWrite(13, LOW);
          RelayOn = false;
        }
      }
      if (millis() - previousMillis > SogNight)
      {
        digitalWrite(13, LOW);
        RelayOn = false;
      }
    }
  }
}