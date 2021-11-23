//*******************************************************
//Reading Current and avraging over 100 milisecond interval
//Do not modify unless explicitly defined by a comment
//*******************************************************
float avg_currentDc(float SysampsDC, float DCcalf, int DcOffset)
{
  float current = 0;
  int sensorValue1 = read_sensor(100,2,1);                   // read the input on analog pin 1(DC Current)
  sensorValue1 = sensorValue1 - DcOffset ;
  current = sensorValue1 * SysampsDC;
  current = current * DCcalf;
  return current;
}

//*******************************************************
//Reading Voltage and avraging over 100 Mili second interval
//*******************************************************
float avg_voltage(float sysvoltsdc)
{
  float voltage = 0;
  int sensorValue1 = read_sensor(100,2,2);                   // read the input on analog pin 2(Voltage to measure)
  voltage = sensorValue1 * sysvoltsdc;
  return voltage;
}

//*******************************************************
//Reading Current and avraging over 100 milisecond interval
//Do not modify unless explicitly defined by a comment
//*******************************************************
float avg_currentAc(float SysampsAC, float ACcalf, int ACOffset, byte ACerror)
{
  float current = 0;
  int sensorValue1 = read_sensor(100,2,3);                   // read the input on analog pin 3(AC Current)
  sensorValue1 = sensorValue1 - ACOffset ;
  if (sensorValue1 <= ACerror)
  {
    return 0;
  }
  current = sensorValue1 * SysampsAC;
  current = current * ACcalf;
  return current;
}

//*******************************************************
//Reading Current and avraging over 100 milisecond interval
//Do not modify unless explicitly defined by a comment
//*******************************************************
float avg_currentMPPT(float SysampsDC, float DCcalf, int DcOffset)
{
  float current = 0;
  int sensorValue1 = read_sensor(100,2,4);                   // read the input on analog pin 4(MPPT Current)
  sensorValue1 = sensorValue1 - DcOffset ;
  current = sensorValue1 * SysampsDC;
  current = current * DCcalf;
  return current;
}


int read_sensor(int mil, int sampleint, int Ainput)
{
  int RunCount = 0;
  int sensorValue1 = 0;
  unsigned long previousMillis = millis();
  while (millis() - previousMillis < mil)
  {
    sensorValue1 = sensorValue1 + analogRead(Ainput);                   // read the input on analog pin 
    delay(sampleint);
    RunCount = RunCount + 1;
  }
  sensorValue1 = sensorValue1 / RunCount;
  return sensorValue1;
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


