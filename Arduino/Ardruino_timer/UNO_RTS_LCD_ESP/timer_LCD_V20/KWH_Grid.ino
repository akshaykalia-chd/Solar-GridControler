/******************************************************
Functions to calculate KWH and Grite time
All calculations of time in milisecomds
********************************************************/

unsigned long Cal_Gridtime(float amps, unsigned long previousMillis)
{
  if (amps < 0)
  {
    unsigned int gtime = millis() - previousMillis;
    return gtime;
  }
  return 0;
}

/**********************************************************/

float Cal_KWH(float amps, unsigned long previousMillis, float ampsac)
{
  if (amps < 0)
  {
    float Watts = ampsac * 255;
    unsigned int time = millis() - previousMillis;
    float WM = Watts * time;
    return WM;

  }
  return 0;
}

float Cal_KWHMPPT(float volts, unsigned long previousMillis, float ampsMPPT)
{
    float Watts = ampsMPPT * volts;
    unsigned int time = millis() - previousMillis;
    float WM = Watts * time;
    return WM;
}