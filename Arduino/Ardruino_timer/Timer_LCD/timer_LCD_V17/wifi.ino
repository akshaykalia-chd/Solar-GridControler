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
  digitalWrite(12, LOW);
  delay (250);
  digitalWrite(12, HIGH);
  delay (2000);
  lcd.setCursor(0, 1);
  lcd.print("Test Wifi          ");
  Serial.println("AT");
  if (Serial.find("OK"))
  {
    lcd.setCursor(0, 1);
    lcd.print("H/W OK     ");

  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("H/W Err      ");
    while (1);
  }
  delay(5000);
}

void SetupEsp8266(String ssid,String pass)
{
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
  TestEsp8266();
  SendCmd("AT+CWQAP",false,2000);
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

