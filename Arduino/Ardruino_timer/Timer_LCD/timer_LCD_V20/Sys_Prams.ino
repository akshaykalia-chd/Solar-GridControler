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
//EPROM Address DC 31,32
//*******************************************************
void set_DcOffset()
{
  int offset = read_4DitiNo(31, 32);
  offset = update_Tcom("DC Offset", offset, 1024);
  store_4DitiNo(offset,31, 32);
}

//*******************************************************
//Function to setup AC current offset
//EPROM Address AC 33,34
//*******************************************************
void set_AcOffset()
{
  int offset = read_4DitiNo(33, 34);
  offset = update_Tcom("AC Offset", offset, 1024);
  store_4DitiNo(offset, 33,34);
}
//*******************************************************
//Function to read/write 4 ditin number from eprom
//*******************************************************
void store_4DitiNo(int offset, int add1, int add2)
{
  byte b1 = offset / 100;
  int temp = b1 * 100;
  byte b2 = offset - temp;
  EEPROM.write(add1, b1);
  EEPROM.write(add2, b2);
}
int read_4DitiNo(int add1, int add2)
{
  byte b1 = EEPROM.read(add1);
  byte b2 = EEPROM.read(add2);
  int temp = b1 * 100;
  temp += b2;
  return temp;
}
//*******************************************************
//Function to get Ontime and OffTime for timers
//Do not modify unless explicitly defined by a comment
//*******************************************************
int get_timer(int timerNo, byte NoOfTimers, String sel)
{
  byte addr = timerNo + 1;
  byte addr1 = addr + NoOfTimers;
  byte addr2 = addr1 + NoOfTimers;
  byte addr3 = addr2 + NoOfTimers;
  if (sel == "OnTime")
  {
    int OnTime = EEPROM.read(addr); //OnHours
    OnTime = OnTime * 100;
    OnTime = OnTime + EEPROM.read(addr1); // On Mins
    return OnTime;
  }
  if (sel == "OffTime")
  {
    int OffTime = EEPROM.read(addr2); // Off Hours
    OffTime = OffTime * 100;
    OffTime = OffTime + EEPROM.read(addr3); // Off Mins
    return OffTime;
  }
}