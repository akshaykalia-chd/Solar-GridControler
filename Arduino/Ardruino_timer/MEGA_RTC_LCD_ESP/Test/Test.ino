#include <Time.h>
#include <DS1307RTC.h>
#include <Wire.h>
void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  setSyncProvider(RTC.get);
  setSyncInterval(3600);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delay (250);
  digitalWrite(12, HIGH);
  delay (2000);
  SendCmd("AT+RST\r\n", 2000,true);
  delay(15000);
  /*SendCmd("AT+CWMODE=1\r\n", 10);
  SendCmd("AT+CWQAP\r\n", 10);
  SendCmd("AT+CWJAP=\"IM4s_Wi_Fi_M4\",\"some_pass\"\r\n", 10000);*/
  SendCmd("AT+CIFSR\r\n", 10,true);
  SendCmd("AT+CIPMUX=1\r\n", 10,true);
  SendCmd("AT+CIPSERVER=1,8888\r\n", 10,true);
}

int runcount = 0;
void loop()
{
  if (runcount > 30)
  {
    SendCmd("AT+CIPSTART=0,\"UDP\",\"192.168.1.101\",8888\r\n", 10,true);
    datalog(1, 1, 2, 3, 5, 18, 07, 12, 19, 12, 23, 5, 14, 32, 18);
    delay(10);
    SendCmd("AT+CIPCLOSE=0", 10,true);
    runcount = 0;
  }
  configlog(1, 42.3, 1.5, 50, 120, 5, 1820, 1920, 1700, 1800, 1400, 1500, 2200, 2300, 0000, 0430, 512, 513, 45, 44, 555, 1024, 1024, 1.25, 22.5, 23.5, 44.5, 46.5, 100.2, 150.63, 300.2, 1000.2);
  runcount++;
  Serial.print(runcount);
}

boolean SendCmd(String cmd, int d, boolean DEBUG)
{
  Serial1.print(cmd);
  String responce = "";
  long int checkpoint = millis();
  boolean result = false;
  while (millis() - checkpoint < d)
  {
    while (Serial1.available())
    {
      char rByte = Serial1.read(); ;
      responce += rByte;
    }
  }
  if (DEBUG == true)
  {
    Serial.println(responce);
    for (int i = 0 ; i < responce.length(); i++)
    {
      String temp = "";
      char tmp = responce[i];
      temp += tmp;
      tmp = responce[i + 1];
      temp += tmp;
      if (temp == "OK")
      {
        result = true;
      }
    }
    return result;
  }
}

