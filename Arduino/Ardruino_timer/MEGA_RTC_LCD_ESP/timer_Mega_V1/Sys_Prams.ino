//*******************************************************
//Function to setup Data Logging
//EPROM Address 31
//*******************************************************
void set_loger()
{
  byte loger = EEPROM.read(33);
  loger = update_Tcom("Loger", loger, 2);
  EEPROM.update(31, loger);
}

//*******************************************************
//Function to setup SOG (Stay On grid time)
//EPROM Address 29 and 30
//*******************************************************
void set_sog()
{
  byte sogM = EEPROM.read(29);
  byte sogN = EEPROM.read(30);
  sogM = update_Tcom("SOG Morning", sogM, 255);
  sogN = update_Tcom("SOG Night", sogN, 255);
  EEPROM.update(29, sogM);
  EEPROM.update(30, sogN);
}

//*******************************************************
//Functions to setup cutoff Voltage and Amps
//EPROM Address 21 to 24 - Volts
//EPROM Address 25 and 28 - Amps
//*******************************************************
void set_cutoffvolts()
{
  update_cutoff(21, "Volts");
}

void set_cutoffamps()
{
  update_cutoff(25, "Amps");
}

//*******************************************************
void update_cutoff(unsigned int addr, String cutcomp)
{
  float cutoff = readFloat(addr);
  while (button() != "Select")
  {
    cutoff = update_btn_float(button(), cutoff, 200.00, 50);
    cutoffdisp(cutoff, cutcomp);
    delay(250);
  }
  writeFloat(addr,cutoff);
  
}

void cutoffdisp(float cutoff, String cutcomp)
{
  lcd.setCursor(0, 1);
  lcd.print("CutOff");
  lcd.setCursor(0, 0);
  lcd.print(cutcomp);
  lcd.print(":");
  lcd.print(cutoff);  
  lcd.print("         ");
}



