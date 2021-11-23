//*******************************************************
//Function to setup System Voltage  
//EPROM Address 21
//*******************************************************
void set_sysvolts()
{
  byte sysvolts = EEPROM.read(21); 
  sysvolts = update_Tcom("System Volts",sysvolts,255);
  EEPROM.write(21,sysvolts);
}
//*******************************************************
//Function to setup System Amps
//EPROM Address 22
//*******************************************************
void set_sysamps()
{
  byte sysamps = EEPROM.read(22); 
  sysamps = update_Tcom("System Amps",sysamps,255);
  EEPROM.write(22,sysamps);
}
//*******************************************************
//Function to setup Data Logging
//EPROM Address 29
//*******************************************************
void set_loger()
{
  byte loger = EEPROM.read(29); 
  loger = update_Tcom("Loger",loger,2);
  EEPROM.write(29,loger);
}
