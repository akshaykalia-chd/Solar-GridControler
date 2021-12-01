//*******************************************************
//This will run on every alarm trigger
//Do not modify unless explicitly defined by a comment
//*******************************************************
void Alarm(byte PageNo)
{
  byte NoOfTimers;
  NoOfTimers = EEPROM.read(0);
  float CutOffApms = EEPROM.read(26) / 100;
  CutOffApms = CutOffApms + EEPROM.read(25);
  for (int i = 0; i < NoOfTimers; i++)
  {
    int HH, MM, cTime, onTime, offTime;
    HH = hour();
    MM = minute();
    cTime = HH * 100;
    cTime = cTime + MM;
    byte addr = i + 1;
    byte addr1 = addr + NoOfTimers;
    byte addr2 = addr1 + NoOfTimers;
    byte addr3 = addr2 + NoOfTimers;
    onTime = EEPROM.read(addr); //OnHours
    onTime = onTime * 100;
    onTime = onTime + EEPROM.read(addr1); // On Mins
    offTime = EEPROM.read(addr2); // Off Hours
    offTime = offTime * 100;
    offTime = offTime + EEPROM.read(addr3); // Off Mins
    if (cTime >= onTime && cTime <= offTime)
    {
      relay_on(cTime, offTime, CutOffApms,PageNo);
    }
    if (cTime >= onTime && offTime <= onTime)
    {
      relay_on(cTime, offTime, CutOffApms,PageNo);
    }
  }
}

void relay_on(int cT, int oT, float cAmps,byte PageNo)
{
  if (cT != oT)
  {
    unsigned long previousMillis = millis();
    digitalWrite(13, HIGH);
    while (cT != oT)
    {
      float volts = avg_voltage();
      float amps = avg_current("DC");
      float ampsac = avg_current("AC");
      float mamps = 0;
      lcd_Display(amps, volts, "On", ampsac,PageNo);
      datalog("On", amps, ampsac, volts);
      int HH = hour();
      int MM = minute();
      cT = HH * 100;
      cT = cT + MM;
    }
    digitalWrite(13, LOW);
  }
}