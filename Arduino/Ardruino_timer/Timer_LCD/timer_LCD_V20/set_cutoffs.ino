//*******************************************************
//Functions to setup cutoff Voltage and Amps
//EPROM Address 23 and 24 - Volts
//EPROM Address 25 and 26 - Amps
//*******************************************************
void set_cutoffvolts()
{
  update_cutoff(23, 24, "Volts");
}

void set_cutoffamps()
{
  update_cutoff(25, 26, "Amps");
}

//*******************************************************
//Functions to setup Calibration factor
//EPROM Address 39 and 40 - DC
//EPROM Address 41 and 42 - AC
//*******************************************************

void set_DcCal()
{
  update_cutoff(39, 40, "DC Cal");
}

void set_AcCal()
{
  update_cutoff(41, 42, "AC Cal");
}

//*******************************************************
void update_cutoff(byte ad1, byte ad2, String cutcomp)
{
  byte PV = EEPROM.read(ad1);
  byte AV = EEPROM.read(ad2);
  while (button() != "Select")
  {
    PV = update_btn(button(), PV, 255, 250);
    cutoffdisp(PV, AV, cutcomp);
  }
  delay(250);
  while (button() != "Select")
  {
    AV = update_btn(button(), AV, 100, 250);
    cutoffdisp(PV, AV, cutcomp);
  }
  EEPROM.update(ad1, PV);
  EEPROM.update(ad2, AV);
  delay(250);
}

void cutoffdisp(byte PD, byte AD, String cutoff)
{
  lcd.setCursor(0, 1);
  lcd.print("CutOff/Calib");
  lcd.print("      ");
  lcd.setCursor(0, 0);
  lcd.print(cutoff);
  lcd.print(":");
  lcd.print(PD);
  lcd.print(".");
  lcd.print(AD);
  lcd.print("      ");
}