void calibrate()
{
  while (1)
  {
    Serial.println("1.Calibrate Sensors.");
    Serial.println("2.Configure WiFI");
    Serial.print("Enter your slection(1-2):");
    int selection = 0;
    while (selection == 0)
    {
      selection = Serial.parseInt();
    }
    Serial.println(selection);
    switch (selection)
    {
      case 1:
        {
          int i = 0;
          int j = 41;
          int k = 61;
          while (i < 9)
          {
            update_sensors(j, k, i);
            j += 2;
            k += 4;
            i++;
          }
        }
        break;
      case 2:
        {
          WiFiconfig();
        }
        break;
      default:
        Serial.println("Wrong Selection");
        break;
    }
  }
}

void update_sensors(unsigned int addr, unsigned int addr1, int SensorNo)
{
  float Calf = 0;
  int offset = 0;
  Serial.print("Current value of Offset for Sensor ");
  Serial.print(SensorNo);
  Serial.print(":");
  Serial.println(readint(addr));
  Serial.print("Enter New Offset for Sensor ");
  Serial.print(SensorNo);
  Serial.print("(1-1024):");
  while (offset == 0)
  {
    offset = Serial.parseInt();
  }
  Serial.println(offset);
  writeint(addr, offset);
  Serial.print("Current value of calibration factor for Sensor ");
  Serial.print(SensorNo);
  Serial.print(":");
  Serial.println(readFloat(addr1));
  Serial.print("Enter New calibration factor for Sensor ");
  Serial.print(SensorNo);
  Serial.print(":");
  while (Calf == 0)
  {
    Calf = Serial.parseFloat();
  }
  Serial.println(Calf);
  writeFloat(addr1, Calf);
}
