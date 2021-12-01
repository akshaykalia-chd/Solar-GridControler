//*******************************************************
//Function to log data using Serial line monitoring over usb
//*******************************************************
void datalog(byte datalogset,byte RelayOn, float amps, float volts, float ampsac, int OnDay, int OnMonth, int OnHour, int OnMinute, float KWH, unsigned long GridTime, float CutOffVolts, float CutOffApms, byte SogMorning, byte SogNight, float sysvoltsdc, float SysampsDC, float SysampsAC, byte NoOfTimers, int ACOffset, int DcOffset, float ACcalf, float DCcalf, byte ACerror, int onTime1, int offTime1, int onTime2, int offTime2, int onTime3, int offTime3, int onTime4, int offTime4, int onTime5, int offTime5) //function to print data on usb
{
  if (datalogset == 1)
  {
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
    Serial.print(amps);
    Serial.print(",");
    Serial.print(volts);
    Serial.print(",");
    Serial.print(ampsac);
    Serial.print(",");
    Serial.print(KWH / 3600000000.00);
    Serial.print(",");
    Serial.print(GridTime / 60000.00);
    Serial.print(",");
    Serial.print(SogMorning);
    Serial.print(",");
    Serial.print(SogNight);
    Serial.print(",");
    Serial.print(CutOffApms);
    Serial.print(",");
    Serial.print(CutOffVolts);
    Serial.print(",");
    Serial.print(sysvoltsdc * 1024.00);
    Serial.print(",");
    Serial.print(SysampsDC * 1024.00);
    Serial.print(",");
    Serial.print(SysampsAC * 1024.00);
    Serial.print(",");
    if (RelayOn == 0)
    {
      Serial.print("Off");
    }
    if (RelayOn == 1)
    {
      Serial.print("On");
    }
    if (RelayOn == 2)
    {
      Serial.print("Timer");
    }
    Serial.print(",");
    Serial.print(ACOffset);
    Serial.print(",");
    Serial.print(DcOffset);
    Serial.print(",");
    Serial.print(DCcalf);
    Serial.print(",");
    Serial.print(ACcalf);
    Serial.print(",");
    Serial.print(ACerror);
    Serial.print(",");
    Serial.print(OnDay);
    Serial.print("/");
    Serial.print(OnMonth);
    Serial.print(" ");
    Serial.print(OnHour);
    Serial.print(":");
    Serial.print(OnMinute);
    Serial.print(",");
    Serial.print(NoOfTimers);
    Serial.print(",");
    Serial.print(onTime1);
    Serial.print(",");
    Serial.print(offTime1);
    Serial.print(",");
    Serial.print(onTime2);
    Serial.print(",");
    Serial.print(offTime2);
    Serial.print(",");
    Serial.print(onTime3);
    Serial.print(",");
    Serial.print(offTime3);
    Serial.print(",");
    Serial.print(onTime4);
    Serial.print(",");
    Serial.print(offTime4);
    Serial.print(",");
    Serial.print(onTime5);
    Serial.print(",");
    Serial.print(offTime5);
    Serial.print(",");
    Serial.print("15");
    Serial.println();
  }
}