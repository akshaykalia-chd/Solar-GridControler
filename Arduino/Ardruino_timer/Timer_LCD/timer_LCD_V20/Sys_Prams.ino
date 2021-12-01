//*******************************************************
//Function to setup System Voltage
//EPROM Address 21
//*******************************************************
void set_sysvolts()
{
  byte sysvolts = EEPROM.read(21);
  sysvolts = update_Tcom("Volts DC", sysvolts, 255);
  EEPROM.write(21, sysvolts);
}
//*******************************************************
//Function to setup System Amps DC
//EPROM Address 22
//*******************************************************
void set_sysamps()
{
  byte sysamps = EEPROM.read(22);
  sysamps = update_Tcom("Amps DC", sysamps, 255);
  EEPROM.write(22, sysamps);
}

//*******************************************************
//Function to setup System Amps AC
//EPROM Address 30
//*******************************************************
void set_sysamps_AC()
{
  byte sysamps = EEPROM.read(30);
  sysamps = update_Tcom("Amps AC", sysamps, 255);
  EEPROM.write(30, sysamps);
}
//*******************************************************
//Function to setup Data Logging
//EPROM Address 29
//*******************************************************
void set_loger()
{
  byte loger = EEPROM.read(29);
  loger = update_Tcom("Loger", loger, 2);
  EEPROM.write(29, loger);
}

//*******************************************************
//Function to setup Ac Zero offset
//EPROM Address 43
//*******************************************************
void set_Aacnl()
{
  byte acnl = EEPROM.read(43);
  acnl = update_Tcom("ACNL", acnl, 255);
  EEPROM.write(43, acnl);
}

//*******************************************************
//Function to setup DC current offset
//EPROM Address DC 31,32,33,34
//*******************************************************
void set_DcOffset()
{
  int offset = get_offset("DC");
  offset = update_Tcom("DC Offset", offset, 1020);
  set_offset("DC", offset);
}

//*******************************************************
//Function to setup AC current offset
//EPROM Address AC 35,36,37,38
//*******************************************************
void set_AcOffset()
{
  int offset = get_offset("AC");
  offset = update_Tcom("AC Offset", offset, 1020);
  set_offset("AC", offset);
}
//*******************************************************
//Function to read/write ofset value
//EPROM Address DC 31,32,33,34
//EPROM Address AC 35,36,37,38
//*******************************************************
int get_offset(String sel)
{
  byte b1 = 0;
  byte b2 = 0;
  byte b3 = 0;
  byte b4 = 0;
  if (sel == "DC")
    {
    b1 = EEPROM.read(31);
    b2 = EEPROM.read(32);
    b3 = EEPROM.read(33);
    b4 = EEPROM.read(34);
    }
  if (sel == "AC")
    {
    b1 = EEPROM.read(35);
    b2 = EEPROM.read(36);
    b3 = EEPROM.read(37);
    b4 = EEPROM.read(38);
    }
int offset = b1 + b2 + b3 + b4;
return offset;
}

void set_offset(String sel, int offset)
{
  byte b1 = 0;
  byte b2 = 0;
  byte b3 = 0;
  byte b4 = 0;
  if (offset <= 255)
  {
    b1 = offset;
  }
  if (offset > 255 && offset <= 510)
  {
    b1 = 255;
    b2 = offset - 255;
  }
  if (offset > 510 && offset <= 765)
  {
    b1 = 255;
    b2 = 255;
    b3 = offset - 510;
  }
  if (offset >= 765)
  {
    b1 = 255;
    b2 = 255;
    b3 = 255;
    b4 = offset - 765;
  }
  if (sel == "DC")
  {
    EEPROM.write(31, b1);
    EEPROM.write(32, b2);
    EEPROM.write(33, b3);
    EEPROM.write(34, b4);
  }
  if (sel == "AC")
  {
    EEPROM.write(35, b1);
    EEPROM.write(36, b2);
    EEPROM.write(37, b3);
    EEPROM.write(38, b4);
  }
}
