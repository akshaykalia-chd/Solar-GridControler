void ConnectServer(String protocol, String IP, String Port)
{
  String cmd = "AT+CIPSTART=0,";
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
  Serial.println("AT");
  if (Serial.find("OK"))
  {
    delay(5000);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi H/W Err");
    while (button() != "Select");
  } 
}

void SetupEsp8266(String ssid,String pass)
{
  boolean connected = connectWiFi(ssid, pass);
  if (!connected)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Conntect Err");
    while (1);
  }
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

