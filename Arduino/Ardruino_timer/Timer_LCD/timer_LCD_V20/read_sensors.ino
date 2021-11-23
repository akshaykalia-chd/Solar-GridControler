//*******************************************************
//Reading Voltage and avraging over 4 second interval 
//*******************************************************
float avg_voltage()
{
  float voltage = 0; 
  int RunCount = 0;
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  while (currentMillis-previousMillis < 300)
  {	
    currentMillis = millis();
    int sensorValue1 = analogRead(A2);                   // read the input on analog pin 1(Voltage to measure)
    delay(10);
    float voltage1 = bat_v(sensorValue1);                // calculating 60v equivalent
    voltage = voltage + voltage1;
    RunCount = RunCount + 1;
  }
  voltage = voltage/RunCount;
  return voltage;
}

//*******************************************************
//Reading Current and avraging over 1 second interval 
//Do not modify unless explicitly defined by a comment
//*******************************************************
float avg_current()
{
  float current = 0; 
  int RunCount = 0;
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  while (currentMillis-previousMillis < 300)
  {	
    currentMillis = millis();
    int sensorValue1 = analogRead(A1);                   // read the input on analog pin 1(Voltage to measure)
    delay(10);
    sensorValue1 = sensorValue1 - 510; 
    if (sensorValue1 < 0)
    {
      sensorValue1 = sensorValue1 * (-1);
    }
    float current1 = bat_c(sensorValue1);                // calculating 60v equivalent
    current = current + current1;
    RunCount = RunCount + 1;
  }
  if (current < 0)
  {
    current = current * (-1);
  }
  current = current/RunCount;
  return current;
}
//*******************************************************
//Functions to calculate 60 volt and 30 amp equivalent
//Do not modify unless explicitly defined by a comment
//*******************************************************
float bat_v (int x)
{
  float ret_bat = x * (EEPROM.read(21)/1023.00);
  return ret_bat;
}

float bat_c (int x)
{
  float ret_c = x * (EEPROM.read(22)/1023.00);
  return ret_c;
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



