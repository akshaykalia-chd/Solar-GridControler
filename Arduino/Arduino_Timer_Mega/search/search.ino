#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // LCD Pin interface
void setup()
{
  lcd.begin(16, 2);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop()
{
  TestEsp8266();
  connectWiFi("IM4s_Wi_Fi_M4","some_pass");
  while (1);
}

void TestEsp8266()
{
  digitalWrite(12, LOW);
  delay (300);
  digitalWrite(12, HIGH);
  boolean found = false;
  long int checkpoint = millis();
  while (millis() - checkpoint < 2000)
  {
    if (Serial1.find("ready"))
    {
      found = true;
    }
  }
  if (!found)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi H/W Err");
    while (1);
  }
}

boolean connectWiFi(String ssid, String pass)
{
  TestEsp8266();
  SendCmd("AT+CWQAP\r\n", 2000, true);
  SendCmd("AT+CWMODE=1\r\n", 2000, true);
  String cmd = "AT+CWJAP=\"";
  cmd += ssid;
  cmd += "\",\"";
  cmd += pass;
  cmd += "\"\r\n";
  boolean connected = (SendCmd(cmd, 15000, true));
  if (!connected)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connection Err");
  }
}

boolean search(String input, String partren)
{
  boolean result = false;
  for (int i = 0 ; i < input.length(); i++)
  {
    String temp = "";
    for (int k = 0 ; k < partren.length(); k++)
    {
      char tmp = input[k + i];
      temp += tmp;
    }
    if (temp == partren)
    {
      result = true;
    }
  }
  return result;
}

boolean SendCmd(String cmd, int d, boolean DEBUG)
{
  Serial1.print(cmd);
  String responce = "";
  long int checkpoint = millis();
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
    return search(responce,"OK");
  }
  return false;
}
