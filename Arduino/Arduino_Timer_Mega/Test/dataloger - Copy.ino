//*******************************************************
//Function to log data using Serial line monitoring over usb
//*******************************************************
void datalog(byte datalogset, byte RelayOn, float amps, float volts, float ampsac, int OnDay, int OnMonth, int OnHour, int OnMinute, float KWH, unsigned long GridTime, float KWHMPPT, float ampsMPPT,float temprature,byte build) //function to print data on usb
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
    data += String (OnDay, DEC);
    data += "/";
    data += String (OnMonth, DEC);
    data += ",";
    data += String (OnHour, DEC);
    data += ":";
    data += String (OnMinute, DEC);
    data += ',';
    data += ftos (ampsMPPT);
    data += ',';
    data += ftos(amps);
    data += ',';
    data += ftos(volts);
    data += ',';
    data += ftos(ampsac);
    data += ',';
    data += ftos(KWH / 3600000000.00);
    data += ',';
    data += ftos (KWHMPPT / 3600000000.00);
    data += ',';
    data += ftos(GridTime / 60000.00);
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
    data += temprature;
    data += ',';
    data += build;
    String cmd ="AT+CIPSEND=0,";
    cmd +=data.length();
    Serial1.println(cmd);
    delay(4);
    Serial1.print(data);
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

