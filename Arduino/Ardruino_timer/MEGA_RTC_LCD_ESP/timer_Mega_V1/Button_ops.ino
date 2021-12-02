//**************************************************************************
// Function to change the paramet valube when UP or Down buttin is presses
//**************************************************************************
int update_btn(String button, unsigned int value, int valmax, int d)
{
  if (value < valmax)
  {
    if (button == "Up")
    {
      value++;
      delay(d);
    }
    if (button == "Down")
    {
      value--;
      delay(d);
    }
  }
  if (value >= valmax)
  {
    if (button == "Down")
    {
      value = valmax - 1;
      delay(d);
    }
    else
      value = 0;
  }
  return value;
}

float update_btn_float(String button, float value, float valmax, int d)
{
  if (value < valmax)
  {
    if (button == "Up")
    {
      value+=0.5;
      delay(d);
    }
    if (button == "Down")
    {
      value-=0.5;
      delay(d);
    }
  }
  if (value >= valmax)
  {
    if (button == "Down")
    {
      value = valmax - 1;
      delay(d);
    }
    else
      value = 0;
  }
  return value;
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
