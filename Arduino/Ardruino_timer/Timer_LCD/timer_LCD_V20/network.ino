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
  EEPROM.write(addr, temp);
  delay (250);
}

void set_port()
{
  int port = read_4DitiNo(35, 36);
  port = update_Tcom("CS Port:", port, 10000);
  store_4DitiNo(port, 33,34);
}

String wificonfig(String sel)
{
  lcd.setCursor(0, 0);
  lcd.print("1.Connect to PC");
  lcd.setCursor(0, 1);
  lcd.print("2.Follow Prompts");
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
  while (inbyte != '\n')
  {
    while (Serial.available())
    {
      inbyte = Serial.read();
      input += inbyte;
    }
  }
return input;
}
