//*******************************************************
//Function to activate relay
//Do not modify unless explicitly defined by a comment
//RelayOn = 0 = Relay is off
//RelayOn = 1 = Relay is On Voltage trigred
//RelayOn = 2 = Relay is On Timer trigred
//*******************************************************
byte activate_relay(float volts, float CutOffVolts, byte RelayOn, int OnTime, int OffTime)
{
  if (RelayOn == 0)
  {
    if (volts < CutOffVolts)
    {
      digitalWrite(13, HIGH);
      //Serial.println("Relay On Vlots condtion meet");
      return 1;
    }
    int HH = hour();
    int MM = minute();
    int cTime = HH * 100;
    cTime = cTime + MM;
    if (cTime >= OnTime && cTime <= OffTime)
    {
      digitalWrite(13, HIGH);
      //Serial.println("Relay On Timer condtion meet");
      return 2;
    }
    if (cTime >= OnTime && OffTime <= OnTime)
    {
      digitalWrite(13, HIGH);
      //Serial.println("Relay On Timer condtion meet");
      return 2;
    }
  }
  return RelayOn;
}

//*******************************************************
//Function to deactivate relay
//Do not modify unless explicitly defined by a comment
//*******************************************************
byte deactivate_relay(float amps, float CutOffApms, unsigned long SogMorning, unsigned long SogNight, byte RelayOn, unsigned long elaptime, int OffTime)
{
  if (RelayOn == 1)
  {
    float mamps = amps * (-1); //moded amps
    if (mamps < CutOffApms)
    {
      digitalWrite(13, LOW);
      //Serial.println("Amps condtion meet");
      return 0;
    }
    if (hour() >= 07 && hour() <= 16)
    {
      if (elaptime > SogMorning)
      {
        digitalWrite(13, LOW);
        //Serial.println("SOGMorning condtion meet");
        return 0;
      }
    }
    if (elaptime > SogNight)
    {
      digitalWrite(13, LOW);
      //Serial.println("SOGNight condtion meet");
      return 0;
    }
  }
  if (RelayOn == 2)
  {
    int HH = hour();
    int MM = minute();
    int cTime = HH * 100;
    cTime = cTime + MM;
    if (cTime == OffTime)
    {
      digitalWrite(13, LOW);
      //Serial.println("offtime reached");
      //Serial.println(OffTime);
      //Serial.println(cTime);
      return 0;
    }
  }
  return RelayOn;
}




