//*******************************************************
//Function to activate relay
//Do not modify unless explicitly defined by a comment
//*******************************************************
void activate_relay()
{
  unsigned long previousMillis = millis();
  float volts = avg_voltage();
  float amps = avg_current("DC");
  float ampsac = avg_current("AC");
  digitalWrite(13, LOW);
  lcd_Display(amps, volts, "Off", ampsac);
  datalog("Off", amps, ampsac, volts);
  boolean RelayOn = false;
  float CutOffVolts = EEPROM.read(24) / 100;
  CutOffVolts = CutOffVolts + EEPROM.read(23);
  float mamps = 0;
  if (volts < CutOffVolts)
  {
    digitalWrite(13, HIGH);
    RelayOn = true;
    float CutOffApms = EEPROM.read(26) / 100;
    CutOffApms = CutOffApms + EEPROM.read(25);
    unsigned long SogMorning = EEPROM.read(27);
    unsigned long SogNight =  EEPROM.read(28);
    SogMorning = SogMorning * 60000;
    SogNight = SogNight * 60000;
    while (millis() - previousMillis < 30000)
    {
      volts = avg_voltage();
      amps = avg_current("DC");
      ampsac = avg_current("AC");
      lcd_Display(amps, volts, "On", ampsac);
      datalog("On", amps, ampsac, volts);
      mamps = amps * (-1); //Moded amps
    }
    while (RelayOn == true)
    {
      lcd_Display(amps, volts, "On", ampsac);
      datalog("On", amps, ampsac, volts);
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


