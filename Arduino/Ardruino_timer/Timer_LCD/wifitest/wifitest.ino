#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // LCD Pin interface
void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(5000);
  lcd.begin(16, 2);
  TestEsp8266();
  SetEsp8266();
  ConnectServer("UDP", "192.168.1.101", "18080");
}
void loop()
{
  senddata("data");
  delay(1000);
}

void ConnectServer(String protocol, String IP, String Port)
{
  SendCmd("AT+CIPMUX=0", false, 1);
  String cmd = "AT+CIPSTART=";
  cmd += '"';
  cmd += protocol;
  cmd += '"';
  cmd += ",";
  cmd += '"';
  cmd += IP;
  cmd += '"';
  cmd += ",";
  cmd += Port;
  SendCmd(cmd, false, 1);
}

void TestEsp8266()
{
  lcd.setCursor(0, 0);
  lcd.print("Test Wifi");
  Serial.println("AT+RST");
  delay(1000);
  if (Serial.find("ready"))
  {
    lcd.setCursor(0, 1);
    lcd.print("H/W OK");

  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("H/W ERR");
    while (1);
  }
}

void SetEsp8266()
{
  String ssid = "ssid";
  String pass = "password";
  boolean connected = connectWiFi(ssid, pass);
  if (!connected)
  {
    lcd.setCursor(0, 1);
    lcd.print("Wifi Error     ");
    while (1);
  }
  lcd.setCursor(0, 1);
  lcd.print("Wifi OK      ");
}

boolean connectWiFi(String ssid, String pass)
{
  SendCmd("AT+CWMODE=1", true, 2000);
  String cmd = "AT+CWJAP=\"";
  cmd += ssid;
  cmd += "\",\"";
  cmd += pass;
  cmd += "\"";
  return SendCmd(cmd, true, 5000);
}

boolean SendCmd(String cmd, boolean debug, int d)
{
  Serial.println(cmd);
  delay(d);
  if (debug == true)
  {
    if (Serial.find("OK"))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

void senddata(String data)
{
  String cipSend = "AT+CIPSEND=";
  cipSend += data.length();
  SendCmd(cipSend, false, 8);
  SendCmd(data, false, 8);
}
