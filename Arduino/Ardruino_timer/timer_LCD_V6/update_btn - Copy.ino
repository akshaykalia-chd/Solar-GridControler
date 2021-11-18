//**************************************************************************
// Function to change the paramet valube when UP or Down buttin is presses
//**************************************************************************
int update_btn(String button, unsigned int value, int valmax,int d)
{
  if(value < valmax)
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
  if(value >= valmax)
  {
    if (button == "Down")
    {
      value = valmax -1;
      delay(d);
    }
    else
      value = 0;
  }
  return value;
}


