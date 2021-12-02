void setup()
{
  Serial.begin(115200);
}

void loop()
{
  for (int i = 0; i < 9; i++)
  {
    update_sensors(0, 0, i);
  }
  while (1);
}

void update_sensors(unsigned int addr, unsigned int addr1, int SensorNo)
{
  float Calf=0;
  int offset=0;
  Serial.print("Enter Offset for Sensor");
  Serial.print(SensorNo);
  Serial.print("(0-1023):");
   while (offset == 0)
  {
    offset = Serial.parseInt();
  }
  Serial.println(offset);
  Serial.print("Enter calibration factor for Sensor");
  Serial.print(SensorNo);
  Serial.print(":");
  while (Calf == 0)
  {
    Calf = Serial.parseFloat();
  }
  Serial.println(Calf);
}
