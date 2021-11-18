#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  writestring(0,"Akshay Kalia");
  Serial.println(readstring(0));
  while(1);
}
/*************************************************************
Reading a float value from EEPROM starting an a given address.
*************************************************************/
float readFloat(unsigned int addr)
{
  union
  {
    byte b[4];
    float f;
  }
  data;
  for (int i = 0; i < 4; i++)
  {
    data.b[i] = EEPROM.read(addr + i);

  }
  return data.f;
}
/*************************************************************
Writing a float value to EEPROM starting an a given address.
*************************************************************/
void writeFloat(unsigned int addr, float x)
{
  union
  {
    byte b[4];
    float f;

  } data;
  data.f = x;
  for (int i = 0; i < 4; i++)
  {
    EEPROM.update(addr + i, data.b[i]);
  }
}
/*************************************************************
Reading a int value from EEPROM starting an a given address.
*************************************************************/
int readint(unsigned int addr)
{
  union
  {
    byte b[2];
    int f;
  }
  data;
  for (int i = 0; i < 2; i++)
  {
    data.b[i] = EEPROM.read(addr + i);

  }
  return data.f;
}

/*************************************************************
Writing a int value to EEPROM starting an a given address.
*************************************************************/
void writeint(unsigned int addr, int x)
{
  union
  {
    byte b[2];
    int f;

  } data;
  data.f = x;
  for (int i = 0; i < 2; i++)
  {
    EEPROM.update(addr + i, data.b[i]);
  }
}

/*************************************************************
Reading a String value from EEPROM starting an a given address.
*************************************************************/
String readstring(unsigned int addr)
{
  unsigned int stringlen = EEPROM.read(addr);
  unsigned int Saddr = addr + 1;
  String out="";
  for (int i = 0; i < stringlen; i++)
  {
    char Rbyte = EEPROM.read(Saddr + i);
    out +=Rbyte;
  }
  return out;
}

/*************************************************************
Writing a String value to EEPROM starting an a given address.
*************************************************************/
void writestring(unsigned int addr, String x)
{
  EEPROM.update(addr,x.length());
  unsigned int Saddr = addr + 1;
   for (int i = 0; i < x.length(); i++)
  {
    EEPROM.update(Saddr + i, x[i]);
  }
}

