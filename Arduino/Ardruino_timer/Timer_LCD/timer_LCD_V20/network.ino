String ipconfig(String sel)
{
  String IP = String (EEPROM.read(44), DEC);
  IP += '.';
  IP += String (EEPROM.read(45), DEC);
  IP += '.';
  IP += String (EEPROM.read(46), DEC);
  IP += '.';
  IP += String (EEPROM.read(47), DEC);
  if (sel == "SET")
  {
    lcd.setCursor(0, 0);
    lcd.print("CS IP          ");
    lcd.setCursor(0, 1);
    lcd.print(IP);
    update_ipcomp(44, IP);
    IP = ipconfig("GET");
    update_ipcomp(45, IP);
    IP = ipconfig("GET");
    update_ipcomp(46, IP);
    IP = ipconfig("GET");
    update_ipcomp(47, IP);
    IP = ipconfig("GET");
  }
  return IP;
}

void update_ipcomp(int addr, String IP)
{
  byte temp = EEPROM.read(addr);
  while (button() != "Select")
  {
    temp = update_btn(button(), temp, 256, 250);
    if ( addr == 44)
    {
      IP = String (temp, DEC);
      IP += '.';
      IP += String (EEPROM.read(45), DEC);
      IP += '.';
      IP += String (EEPROM.read(46), DEC);
      IP += '.';
      IP += String (EEPROM.read(47), DEC);
    }
    if ( addr == 45)
    {
      IP = String (EEPROM.read(44), DEC);
      IP += '.';
      IP += String (temp, DEC);
      IP += '.';
      IP += String (EEPROM.read(46), DEC);
      IP += '.';
      IP += String (EEPROM.read(47), DEC);
    }
    if ( addr == 46)
    {
      IP = String (EEPROM.read(44), DEC);
      IP += '.';
      IP += String (EEPROM.read(45), DEC);
      IP += '.';
      IP += String (temp, DEC);
      IP += '.';
      IP += String (EEPROM.read(47), DEC);
    }
    if ( addr == 47)
    {
      IP = String (EEPROM.read(44), DEC);
      IP += '.';
      IP += String (EEPROM.read(45), DEC);
      IP += '.';
      IP += String (EEPROM.read(46), DEC);
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
  int port = read_4DitiNo(35, 36);
  port = update_Tcom("CS Port:", port, 10000);
  store_4DitiNo(port, 35, 36);
}

/**************************************
Read Wifi parameters from Serial Port
***************************************/
String SreadWiFiconfig(String sel)
{
  lcd.setCursor(0, 0);
  lcd.print("1.Connect to PC");
  lcd.setCursor(0, 1);
  lcd.print("2.Turn-off Mains");
  if (sel == "GETSSID")
  {
    Serial.println("Eenter SSID:");
  }
  if (sel == "GETPASS")
  {
    Serial.println("Eenter Password:");
  }
  String input = "";
  char inbyte = ' ';
  while (inbyte != '\n')
  {
    while (Serial.available())
    {
      inbyte = Serial.read();
      if (inbyte != '\n')
      {
        input += inbyte;
      }
    }
  }
  return input;
}

void WiFiconfig()
{
  String SSID = SreadWiFiconfig("GETSSID");
  String PASS = SreadWiFiconfig("GETPASS");
  Serial.println("1.Turn-on Mains");
  Serial.println("Waiting for 10 Seconds");
  delay(10000);
  SetupEsp8266(SSID, PASS);
}
