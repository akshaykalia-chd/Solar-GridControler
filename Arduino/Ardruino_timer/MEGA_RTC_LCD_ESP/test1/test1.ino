void setup()
{
 Serial.begin(115200);
  // put your setup code here, to run once:
}

void loop() 
{
  delay(300);
  float tempread = read_sensor(8, 0,0);
  Serial.println(tempread*437);
  
}

float read_sensor(byte aInput, int sOffset, byte sAddr)
{
  //setAddr(sAddr);
  int sensorValue = 0;
  unsigned long pmillis = millis();
  while (millis() - pmillis < 20)
  {
    int Inval1 = analogRead(aInput);
    if (Inval1 > sensorValue)
    {
      sensorValue = Inval1;
    }
  }
  sensorValue -= sOffset;
  return sensorValue/1023.00;
}

