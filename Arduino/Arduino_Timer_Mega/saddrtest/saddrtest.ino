void setup()
{
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(29, OUTPUT);
  Serial.begin(115200);
}

void loop()
{

  Serial.println(read_sensor(1, 0, 4));

}

float read_sensor(byte aInput, int sOffset, byte sAddr)
{
  setAddr(sAddr);
  int sensorValue = 0;
  unsigned long pmillis = millis();
  while (millis() - pmillis < 20)
  {
    int Inval1 = analogRead(aInput);
    Inval1 -= sOffset;
    if (Inval1 > sensorValue)
    {
      sensorValue = Inval1;
    }
  }
  return sensorValue / 1023.00;
}

void setAddr(byte sAddr)
{
  switch (sAddr)
  {
    case 0:
      digitalWrite(23, LOW);
      digitalWrite(25, LOW);
      digitalWrite(27, LOW);
      digitalWrite(29, LOW);
      break;
    case 1:
      digitalWrite(23, HIGH);
      digitalWrite(25, LOW);
      digitalWrite(27, LOW);
      digitalWrite(29, LOW);
      break;
    case 2:
      digitalWrite(23, LOW);
      digitalWrite(25, HIGH);
      digitalWrite(27, LOW);
      digitalWrite(29, LOW);
      break;
    case 3:
      digitalWrite(23, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(27, LOW);
      digitalWrite(29, LOW);
      break;
    case 4:
      digitalWrite(23, LOW);
      digitalWrite(25, LOW);
      digitalWrite(27, HIGH);
      digitalWrite(29, LOW);
      break;
    case 5:
      digitalWrite(23, HIGH);
      digitalWrite(25, LOW);
      digitalWrite(27, HIGH);
      digitalWrite(29, LOW);
      break;
    case 6:
      digitalWrite(23, LOW);
      digitalWrite(25, HIGH);
      digitalWrite(27, HIGH);
      digitalWrite(29, LOW);
      break;
    case 7:
      digitalWrite(23, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(27, HIGH);
      digitalWrite(29, LOW);
      break;
    case 8:
      digitalWrite(23, LOW);
      digitalWrite(25, LOW);
      digitalWrite(27, LOW);
      digitalWrite(29, HIGH);
      break;
    case 9:
      digitalWrite(23, HIGH);
      digitalWrite(25, LOW);
      digitalWrite(27, LOW);
      digitalWrite(29, HIGH);
      break;
    case 10:
      digitalWrite(23, LOW);
      digitalWrite(25, HIGH);
      digitalWrite(27, LOW);
      digitalWrite(29, HIGH);
      break;
    case 11:
      digitalWrite(23, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(27, LOW);
      digitalWrite(29, HIGH);
      break;
    case 12:
      digitalWrite(23, LOW);
      digitalWrite(25, LOW);
      digitalWrite(27, HIGH);
      digitalWrite(29, HIGH);
      break;
    case 13:
      digitalWrite(23, HIGH);
      digitalWrite(25, LOW);
      digitalWrite(27, HIGH);
      digitalWrite(29, HIGH);
      break;
    case 14:
      digitalWrite(23, LOW);
      digitalWrite(25, HIGH);
      digitalWrite(27, HIGH);
      digitalWrite(29, HIGH);
      break;
    case 15:
      digitalWrite(23, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(27, HIGH);
      digitalWrite(29, HIGH);
      break;
  }
}

