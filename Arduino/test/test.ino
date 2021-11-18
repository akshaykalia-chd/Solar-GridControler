void setup()
{
  Serial.begin(115200);
}

void loop()
{
  int runcount = 0;
  while (runcount != 1000)
  {
    Serial.print(runcount);
    Serial.print(",");
    read_sensor();
    runcount++;
  }
  while (1);
}

 int read_sensor()
{
  int runcount = 0;
  int count = 1000;
  int samples = 0;
  unsigned long sensorValue = 0;
  while (samples != count)
  {
    int sample = 0;
    while (runcount != 30)
    {
      int Inval1 = analogRead(2);
      if (Inval1 > sample)
      {
        sample = Inval1;
      }
      runcount++;
    }
    if (sensorValue < sample)
    {
      sensorValue = sample;
    }
    samples++;
    runcount = 0;
  }
  int ret = sensorValue;
  Serial.println(ret);
  return ret;
}

