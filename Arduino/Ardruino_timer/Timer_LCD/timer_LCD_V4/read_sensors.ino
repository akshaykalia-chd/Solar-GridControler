//*******************************************************
//Reading Voltage and avraging over 4 second interval 
//*******************************************************
float avg_voltage()
{
  float voltage = 0; 
  int RunCount = 0;
  int sensorValue1 = 0;
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  while (currentMillis-previousMillis < 100)
  {	
    currentMillis = millis();
    sensorValue1 = sensorValue1 + analogRead(A2);                   // read the input on analog pin 1(Voltage to measure)
    delay(1);
    RunCount = RunCount + 1;
  }
  sensorValue1= sensorValue1/RunCount;
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
  float time = 0;
  float KW = 0;
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  int timem = 0;
  while (timem < 100)
  { 
    timem = currentMillis - previousMillis;	
    currentMillis = millis();
    if (sel == "DC")
    {
      sensorValue1 = sensorValue1 + analogRead(A1);                   // read the input on analog pin 1(Voltage to measure)
      delay(2);      
    }
    if (sel == "AC")
    {
      sensorValue1 = sensorValue1 + analogRead(A3);                   // read the input on analog pin 1(Voltage to measure)
      delay(2); 
    }
    RunCount = RunCount + 1;
   }
  sensorValue1 = sensorValue1/RunCount;
  if (sel == "DC")
    {
      sensorValue1 = sensorValue1 - 484;
    }
  if (sel == "AC")
    {
      sensorValue1 = sensorValue1 - 488;
    }
  current = bat_c(sensorValue1);
  if (sel == "AC")
  {
    time = timem/3600000;
    KW = current * 250;
    KW = KW * time;
    KWH = KWH + KW;
  }
  return current;
}
//*******************************************************
//Functions to calculate 60 volt and 30 amp equivalent
//Do not modify unless explicitly defined by a comment
//*******************************************************
float bat_v (int x)
{
  float ret_bat = x * (EEPROM.read(21)/1024.00);
  return ret_bat;
}

float bat_c (int x)
{
  float ret_c = x * (EEPROM.read(22)/1024.00);
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


