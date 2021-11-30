//*******************************************************
//Function to activate relay
//Do not modify unless explicitly defined by a comment
//*******************************************************
void activate_relay(unsigned int GridTime)
{
  float volts=avg_voltage();
  float amps=avg_current("DC");
  float ampsac=avg_current("AC");
  digitalWrite(13, LOW);
  lcd_Display(amps,volts,"Off",GridTime,ampsac);
  datalog("Off");
  boolean RelayOn = false;
  float CutOffVolts = EEPROM.read(24)/100;
  CutOffVolts = CutOffVolts + EEPROM.read(23);
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();
  if (volts < CutOffVolts)
  {
    digitalWrite(13, HIGH);
    RelayOn = true;
    float CutOffApms = EEPROM.read(26)/100;
    CutOffApms= CutOffApms + EEPROM.read(25);
    unsigned long SogMorning = EEPROM.read(27);
    unsigned long SogNight =  EEPROM.read(28);
    SogMorning = SogMorning * 60000;
    SogNight = SogNight * 60000;
    while (RelayOn == true)
    {
      currentMillis = millis();
      lcd_Display(amps,volts,"On",GridTime,ampsac);
      datalog("On");
      volts=avg_voltage();
      amps=avg_current("DC");
      ampsac=avg_current("AC");
      delay(2000);
      if (amps < CutOffApms)
      {
        digitalWrite(13, LOW);
        RelayOn = false;
      }
      if (hour()>=07 && hour()<=16)
      {
        if (currentMillis - previousMillis > SogMorning)
        {
          digitalWrite(13, LOW);
          RelayOn = false;
        }
      }
      if (currentMillis - previousMillis > SogNight)
      {
        digitalWrite(13, LOW);
        RelayOn = false;
      }
    }
  }
}