//*******************************************************
//Function to setup SOG (Stay On grid time)
//EPROM Address 27 and 28
//*******************************************************
void set_sog()
{
  byte sogM = EEPROM.read(27);
  byte sogN = EEPROM.read(28);
  sogM = update_Tcom("SOG Morning", sogM, 255);
  sogN = update_Tcom("SOG Night", sogN, 255);
  EEPROM.write(27, sogM);
  EEPROM.write(28, sogN);
}


