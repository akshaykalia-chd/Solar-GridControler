//*******************************************************
//Function to log data using Serial line monitoring over usb
//*******************************************************
void datalog(byte datalogset, byte RelayOn, float amps, float volts, float ampsac, int OnDay, int OnMonth, int OnHour, int OnMinute, float KWH, unsigned long GridTime, float CutOffVolts, float CutOffApms, byte SogMorning, byte SogNight, float sysvoltsdc, float SysampsDC, float SysampsAC, byte NoOfTimers, int ACOffset, int DcOffset, float ACcalf, float DCcalf, byte ACerror, int onTime1, int offTime1, int onTime2, int offTime2, int onTime3, int offTime3, int onTime4, int offTime4, int onTime5, int offTime5) //function to print data on usb
{
  if (datalogset == 1)
  {
    String data = "";
    data += String (day(), DEC);
    data += '/';
    data += String (month(), DEC);
    data += '/';
    data += String(year(), DEC);
    data += ',';
    data += String(hour(), DEC);
    data += ':';
    data += String (minute(), DEC);
    data += ':';
    data += String (second(), DEC);
    data += ',';
    data += ftos(amps);
    data += ',';
    data += ftos(volts);
    data += ',';
    data += ftos(ampsac);
    data += ',';
    data += ftos(KWH / 3600000000.00);
    data += ',';
    data += ftos(GridTime / 60000.00);
    data += ',';
    data += String (SogMorning, DEC);
    data += ',';
    data += String (SogNight, DEC);
    data += ',';
    data += ftos (CutOffApms);
    data += ',';
    data += ftos (CutOffVolts);
    data += ',';
    data += ftos(sysvoltsdc * 1024.00);
    data += ',';
    data += ftos(SysampsDC * 1024.00);
    data += ',';
    data += ftos(SysampsAC * 1024.00);
    data += ',';
    if (RelayOn == 0)
    {
      data += "Off";
    }
    if (RelayOn == 1)
    {
      data += "On";
    }
    if (RelayOn == 2)
    {
      data += "Timer";
    }
    data += ',';
    data += String(ACOffset, DEC);
    data += ',';
    data += String (DcOffset, DEC);
    data += ',';
    data += ftos(DCcalf);
    data += ',';
    data += ftos(ACcalf);
    data += ',';
    data += String (ACerror, DEC);
    data += ',';
    data += String (OnDay, DEC);
    data += "/";
    data += String (OnMonth, DEC);
    data += " ";
    data += String (OnHour, DEC);
    data += ":";
    data += String (OnMinute, DEC);
    data += ',';
    data += String (NoOfTimers, DEC);
    data += ',';
    data += String (onTime1, DEC);
    data += ',';
    data += String (offTime1, DEC);
    data += ',';
    data += String (onTime2, DEC);
    data += ',';
    data += String (offTime2, DEC);
    data += ',';
    data += String (onTime3, DEC);
    data += ',';
    data += String (offTime3, DEC);
    data += ',';
    data += String (onTime4, DEC);
    data += ',';
    data += String (offTime4, DEC);
    data += ',';
    data += String (onTime5, DEC);
    data += ',';
    data += String (offTime5, DEC);
    data += ',';
    data += "16";
    String cipSend = "AT+CIPSEND=";
    cipSend += data.length();
    Serial.println(cipSend);
    delay(10);
    Serial.println(data);
    //SendCmd(cipSend, false, 8);
    //SendCmd(data, false, 8);
  }
}


String ftos (float a)
{
  String y = "";
  if (a < 0)
  {
    a = a * -1;
    y += '-';
  }
  int PD = a;
  y += String (PD, DEC);
  float temp = a - PD;
  int AD = temp * 100;
  if ( AD < 10)
  {
    y += ".0";
    y += String (AD, DEC);
    return y;
  }
  y += '.';
  y += String(AD, DEC);
  return y;
}