//*******************************************************
//Reading Voltage and avraging over 100 Mili second interval
//*******************************************************
float avg_voltage()
{
  float voltage = 0;
  int RunCount = 0;
  int sensorValue1 = 0;
  unsigned long previousMillis = millis();
  while (millis() - previousMillis < 100)
  {
    sensorValue1 = sensorValue1 + analogRead(A2);                   // read the input on analog pin 2(Voltage to measure)
    delay(2);
    RunCount = RunCount + 1;
  }
  sensorValue1 = sensorValue1 / RunCount;
  voltage = bat_v(sensorValue1);
  return voltage;
}

//*******************************************************
//Reading Current and avraging over 1 second interval
//Do not modify unless explicitly defined by a comment
//*******************************************************
float avg_current(String sel)
{
  float current = 0;
  int RunCount = 0;
  int sensorValue1 = 0;
  unsigned long previousMillis = millis();
  while (millis() - previousMillis < 100)
  {
    if (sel == "DC")
    {
      sensorValue1 = sensorValue1 + analogRead(A1);                   // read the input on analog pin 1(DC Current)
      delay(2);
    }
    if (sel == "AC")
    {
      sensorValue1 = sensorValue1 + analogRead(A3);                   // read the input on analog pin 3(AC Current)
      delay(2);
    }
    RunCount = RunCount + 1;
   }
  sensorValue1 = sensorValue1 / RunCount;
  if (sel == "DC")
  {
    sensorValue1 = sensorValue1 - get_offset("DC");
    current = bat_c(sensorValue1, "DC");
    if (current < 0)
    {
      GridTime = GridTime + millis() - previousMillis0;
    }

  }
  if (sel == "AC")
  {
    sensorValue1 = sensorValue1 - get_offset("AC");
    current = bat_c(sensorValue1, "AC");
    float Watts = 0;
    Watts = current * 255;
    unsigned int time = millis() - previousMillis0;
    float WM = Watts * time;
    KWH = KWH + WM;
    if (GridTime != 0)
    {
    previousMillis0 = GridTime;
    }
   }
  return current;
}
//*******************************************************
//Functions to calculate volts and amps equivalent
//Do not modify unless explicitly defined by a comment
//*******************************************************
float bat_v (int x)
{
  float ret_bat = x * (EEPROM.read(21) / 1024.00);
  return ret_bat;
}

float bat_c (int x, String sel)
{
  if (sel == "DC")
  {
    float ret_c = x * (EEPROM.read(22) / 1024.00);
    float calf = EEPROM.read(40) / 100.00;
    calf = calf + EEPROM.read(39);
    ret_c = ret_c * calf;
    return ret_c;
  }
  if (sel == "AC")
  {
    if (x <= EEPROM.read(43))
    {
      return 0;
    }
    float ret_c = EEPROM.read(30) / 1024.00;
    ret_c = x * ret_c;
    float calf = EEPROM.read(42) / 100.00;
    calf = calf + EEPROM.read(41);
    ret_c = ret_c * calf;
    return ret_c;
  }
}

//*******************************************************
//Functions to read a press of a button
//Do not modify unless explicitly defined by a comment
//*******************************************************
String button()
{
  int sensorValue0 = analogRead(A0);
  if (sensorValue0 < 5)
    return ("Right");
  if (sensorValue0 > 95 && sensorValue0 <= 100)
    return ("Up");
  if (sensorValue0 > 250 && sensorValue0 <= 255)
    return ("Down");
  if (sensorValue0 > 404 && sensorValue0 <= 408)
    return ("Left");
  if (sensorValue0 > 635 && sensorValue0 <= 640)
    return ("Select");
  return ("None");
}