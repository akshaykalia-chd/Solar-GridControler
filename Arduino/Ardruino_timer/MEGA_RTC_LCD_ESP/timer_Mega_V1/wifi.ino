/****************************************************************
Functions to Test the WiFi hardware
****************************************************************/
void TestEsp8266()
{
  boolean found = false;
  digitalWrite(12, LOW);
  delay (300);
  digitalWrite(12, HIGH);
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

/****************************************************************
Functions to Connect to a WiFi Network
****************************************************************/
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
  boolean connected = (SendCmd(cmd, 20000, true));
  if (!connected)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connection Err");
    Serial.println("Connection Error");
  }
}

/****************************************************************
Functions to search a patren in Wifi module responce to a WiFi Network
****************************************************************/
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

/****************************************************************
Send a command to WiFi module
****************************************************************/
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
  }
  return search(responce, "OK");
}

/****************************************************************
Function to setup with CS IP
****************************************************************/
String ipconfig(String sel)
{
  String IP = String (EEPROM.read(32), DEC);
  IP += '.';
  IP += String (EEPROM.read(33), DEC);
  IP += '.';
  IP += String (EEPROM.read(34), DEC);
  IP += '.';
  IP += String (EEPROM.read(35), DEC);
  if (sel == "SET")
  {
    lcd.setCursor(0, 0);
    lcd.print("CS IP          ");
    lcd.setCursor(0, 1);
    lcd.print(IP);
    update_ipcomp(32, IP);
    IP = ipconfig("GET");
    update_ipcomp(33, IP);
    IP = ipconfig("GET");
    update_ipcomp(34, IP);
    IP = ipconfig("GET");
    update_ipcomp(35, IP);
    IP = ipconfig("GET");
  }
  return IP;
}

/****************************************************************
Function to setup with CS IP
****************************************************************/
void update_ipcomp(int addr, String IP)
{
  byte temp = EEPROM.read(addr);
  while (button() != "Select")
  {
    temp = update_btn(button(), temp, 256, 250);
    if ( addr == 32)
    {
      IP = String (temp, DEC);
      IP += '.';
      IP += String (EEPROM.read(33), DEC);
      IP += '.';
      IP += String (EEPROM.read(34), DEC);
      IP += '.';
      IP += String (EEPROM.read(35), DEC);
    }
    if ( addr == 33)
    {
      IP = String (EEPROM.read(32), DEC);
      IP += '.';
      IP += String (temp, DEC);
      IP += '.';
      IP += String (EEPROM.read(34), DEC);
      IP += '.';
      IP += String (EEPROM.read(35), DEC);
    }
    if ( addr == 34)
    {
      IP = String (EEPROM.read(32), DEC);
      IP += '.';
      IP += String (EEPROM.read(33), DEC);
      IP += '.';
      IP += String (temp, DEC);
      IP += '.';
      IP += String (EEPROM.read(35), DEC);
    }
    if ( addr == 35)
    {
      IP = String (EEPROM.read(32), DEC);
      IP += '.';
      IP += String (EEPROM.read(33), DEC);
      IP += '.';
      IP += String (EEPROM.read(34), DEC);
      IP += '.';
      IP += String (temp, DEC);
    }
    lcd.setCursor(0, 1);
    lcd.print(IP);
    lcd.print("  ");
  }
  EEPROM.update(addr, temp);
  delay (250);
}
/**********************************
Store CS port no in Eprom
Eprom Address 35, 36
***********************************/
void set_port()
{
  int port = readint(36);
  port = update_Tcom("CS Port:", port, 10000);
  writeint(36, port);
}

/**************************************
Read Wifi parameters from Serial Port
***************************************/
String SreadWiFiconfig(String sel)
{
  if (sel == "GETSSID")
  {
    Serial.print("Eenter SSID:");
  }
  if (sel == "GETPASS")
  {
    Serial.print("Eenter Password:");
  }
  String input = "";
  char inbyte = ' ';
  while (inbyte != '\r')
  {
    while (Serial.available())
    {
      inbyte = Serial.read();
      if (inbyte != '\n' && inbyte != '\r')
      {
        input += inbyte;
      }
    }
  }
  Serial.println(input);
  return input;
}

void WiFiconfig()
{
  String SSID = SreadWiFiconfig("GETSSID");
  String PASS = SreadWiFiconfig("GETPASS");
  connectWiFi(SSID, PASS);
}


