//*******************************************************
//This will run on every alarm trigger 
//Do not modify unless explicitly defined by a comment
//*******************************************************
void Alarm()
{
  byte NoOfTimers;
  NoOfTimers = EEPROM.read(0);
  float CutOffApms = EEPROM.read(26)/100;
  CutOffApms= CutOffApms + EEPROM.read(25);
  for(int i = 0; i < NoOfTimers; i++)
  {
    int HH,MM,cTime,onTime,offTime;
    HH=hour();
    MM=minute();
    cTime=HH*100;
    cTime=cTime+MM;
    byte addr = i+1;
    byte addr1 = addr+NoOfTimers;
    byte addr2 = addr1+NoOfTimers;
    byte addr3 = addr2+NoOfTimers;
    onTime=EEPROM.read(addr); //OnHours
    onTime=onTime*100;
    onTime=onTime+EEPROM.read(addr1); // On Mins
    offTime=EEPROM.read(addr2); // Off Hours
    offTime=offTime*100;
    offTime=offTime+EEPROM.read(addr3); // Off Mins
    if(cTime >= onTime && cTime <= offTime)
    {
      relay_on(cTime,offTime,CutOffApms);
    }
    if(cTime >= onTime && offTime <= onTime)
    {
      relay_on(cTime,offTime,CutOffApms);
    }
  }
}

void relay_on(int cT,int oT,float cAmps)
{
  while(cT != oT)
  {
    unsigned long previousMillis = millis();
    digitalWrite(13, HIGH);
    float volts=avg_voltage();
    float amps=avg_current("DC");
    cal_gridtime(amps,previousMillis);
    float ampsac=avg_current("AC");
    lcd_Display(amps,volts,"On",ampsac);
    datalog("On",amps,ampsac,volts);
    delay(2000);
    float mamps = amps * (-1); //Moded amps
    if(mamps < cAmps)
    {
      digitalWrite(13, LOW);
      int HH=hour();
      int MM=minute();
      int cTime=HH*100;
      cTime=cTime+MM;
      while (cTime != oT)
        {
        previousMillis = millis();
        float CutOffVolts = EEPROM.read(24)/100;
        CutOffVolts = CutOffVolts + EEPROM.read(23);
        float volts=avg_voltage();
        float amps=avg_current("DC");
        cal_gridtime(amps,previousMillis);
        float ampsac=avg_current("AC");
        lcd_Display(amps,volts,"Off",ampsac);
        datalog("Off",amps,ampsac,volts);
        if (volts < CutOffVolts)
         {
          return;
         }
        }
    }
  }
}

