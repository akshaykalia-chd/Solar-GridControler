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
  TimerNos = update_Tcom("TimerNos",TimerNos,6);
  EEPROM.write(0,TimerNos);
  byte TimerComp = 0;
  for(byte i = 0; i < TimerNos; i++)
  {
    byte addr = i+1;
    byte addr1 = addr+TimerNos;
    byte addr2 = addr1+TimerNos;
    byte addr3 = addr2+TimerNos;
    TimerComp=update_timer(i+1,24,EEPROM.read(addr),"On Hour"); 
    EEPROM.write(addr,TimerComp);
    print_timers(addr,i+1,"On Hour",TimerComp);
    delay(250);
    TimerComp=update_timer(i+1,60,EEPROM.read(addr1),"On Minute");
    EEPROM.write(addr1,TimerComp);
    print_timers(addr1,i+1,"On Minute",TimerComp);
    delay(250);
    TimerComp=update_timer(i+1,24,EEPROM.read(addr2),"Off Hour"); 
    EEPROM.write(addr2,TimerComp);
    print_timers(addr2,i+1,"Off Hour",TimerComp);
    delay(250);
    TimerComp=update_timer(i+1,60,EEPROM.read(addr3),"Off Minute");
    EEPROM.write(addr3,TimerComp);
    print_timers(addr3,i+1,"Off Minute",TimerComp);
  }
} 

byte update_timer(byte TimerNo, byte TimerValueMax,byte TimerValue,String TimerCom)
{
  lcd.setCursor(0,1);
  lcd.print("Timer ");
  lcd.print(TimerNo);    
  TimerValue = update_Tcom(TimerCom,TimerValue,TimerValueMax);
  return TimerValue;
}

void print_timers(byte a,byte b,String comps,byte val)
{
  Serial.print("EP Rom address ");
  Serial.print(a);
  Serial.print(" ");
  Serial.print(comps);
  Serial.print(" Timer ");
  Serial.print(b);
  Serial.print("-");
  Serial.print(val);  
  Serial.println();
}



