//*******************************************************
//Function to log data using Serial line monitoring over usb
//*******************************************************
void datalog(String RelayStatus) //function to print data on usb
{
  if (EEPROM.read(29) == 1)
  {
    byte NoOffTimers = EEPROM.read(0);  
    Serial.print(day());
    Serial.print("/");
    Serial.print(month());
    Serial.print("/");
    Serial.print(year()); 
    Serial.print(",");
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.print(",");
    Serial.print(avg_current());
    Serial.print(",");
    Serial.print(avg_voltage());
    Serial.print(",");
    Serial.print(EEPROM.read(27));
    Serial.print(",");
    Serial.print(EEPROM.read(28));
    Serial.print(",");
    Serial.print(EEPROM.read(25));
    Serial.print(".");
    Serial.print(EEPROM.read(26));
    Serial.print(",");
    Serial.print(EEPROM.read(23));
    Serial.print(".");
    Serial.print(EEPROM.read(24));
    Serial.print(",");
    Serial.print(EEPROM.read(21));
    Serial.print(",");
    Serial.print(EEPROM.read(22));
    Serial.print(",");
    Serial.print(RelayStatus);
    Serial.print(",");
    Serial.print(NoOffTimers);
    for(int i = 0; i < NoOffTimers; i++)
    {
      byte addr = i+1;
      byte addr1 = addr+NoOffTimers;
      byte addr2 = addr1+NoOffTimers;
      byte addr3 = addr2+NoOffTimers;  
      Serial.print(",");
      Serial.print(EEPROM.read(addr));
      Serial.print(EEPROM.read(addr1));
      Serial.print(",");
      Serial.print(EEPROM.read(addr2));
      Serial.print(EEPROM.read(addr3));
    }
    Serial.println();    
  }
}

