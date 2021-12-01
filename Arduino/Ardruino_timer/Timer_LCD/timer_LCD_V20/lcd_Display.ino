//*******************************************************
//Function to display data on LCD
//*******************************************************
void lcd_Display(float amps, float volts, String Rstate, float ampsac, byte PageNo)
{
  if (PageNo == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("IM4S SSGMC M-1");
    lcd.print("            ");
    lcd.setCursor(0, 1);
    lcd.print("Code Build:11");
    lcd.print("             ");
  }
  if (PageNo == 1)
  {
    digitalClockDisplay();
  }
  if (PageNo == 2)
  {
    lcd.setCursor(0, 0);
    lcd.print("KWH used:");
    lcd.print(KWH / 3600000000);
    lcd.print("           ");
    lcd.setCursor(0, 1);
    lcd.print("TGT(Min):");
    lcd.print(GridTime / 60000);
    lcd.print("           ");
  }
  if (PageNo == 3)
  {
    lcd.setCursor(0, 0);
    lcd.print("DC volts:");
    lcd.print(volts);
    lcd.print("V");
    lcd.print("             ");
    lcd.setCursor(0, 1);
    lcd.print("DC Amps:");
    lcd.print(amps);
    lcd.print("A");
    lcd.print("             ");
  }
  if (PageNo == 4)
  {
    lcd.setCursor(0, 0);
    lcd.print("AC Volts:255V");
    lcd.print("             ");
    lcd.setCursor(0, 1);
    lcd.print("AC Amps:");
    lcd.print(ampsac);
    lcd.print("A");
    lcd.print("             ");
  }

  if (PageNo == 5)
  {
    lcd.setCursor(0, 0);
    lcd.print("Grid Supply:");
    lcd.print(Rstate);
    lcd.print("         ");
    lcd.setCursor(0, 1);
    int runtime = 100 / amps;
    runtime = runtime * 0.4;
    if (runtime < 0)
    {
      lcd.print("Run Time(H):");
      lcd.print("CHRG");
    }
    lcd.print("Run Time(H):");
    lcd.print(runtime);
    lcd.print("         ");
  }
  if (PageNo == 6)
  {
    lcd.setCursor(0, 0);
    lcd.print("Off Amps:");
    lcd.print(EEPROM.read(25));
    lcd.print(".");
    lcd.print(EEPROM.read(26));
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("On Volts:");
    lcd.print(EEPROM.read(23));
    lcd.print(".");
    lcd.print(EEPROM.read(24));
    lcd.print("         ");
  }
  if (PageNo == 7)
  {
    lcd.setCursor(0, 0);
    lcd.print("SOG AM(M):");
    lcd.print(EEPROM.read(27));
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("SOG PM(M):");
    lcd.print(EEPROM.read(28));
    lcd.print("         ");
  }
  if (PageNo == 8)
  {
    lcd.setCursor(0, 0);
    lcd.print("Sys Volts:");
    lcd.print(EEPROM.read(21));
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("Sys Amps DC:");
    lcd.print(EEPROM.read(22));
    lcd.print("         ");
  }
  if (PageNo == 9)
  {
    lcd.setCursor(0, 0);
    lcd.print("Sys Amps AC:");
    lcd.print(EEPROM.read(30));
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("Zero Err AC:");
    lcd.print(EEPROM.read(43));
    lcd.print("         ");
  }
}
//*******************************************************
//Function to display date and time
//Do not modify unless explicitly defined by a comment
//*******************************************************
void digitalClockDisplay() // digital clock display of the time
{
  lcd.setCursor(0, 0);
  printDigits(day());
  lcd.print("/");
  printDigits(month());
  lcd.print("/");
  printDigits(year());
  lcd.print("         ");
  lcd.setCursor(0, 1);
  printDigits(hour());
  lcd.print(":");
  printDigits(minute());
  lcd.print(":");
  printDigits(second());
  lcd.print("         ");
}
//*******************************************************
// utility function prints preceding colon and leading 0 for date and time
//Do not modify unless explicitly defined by a comment
//*******************************************************
void printDigits(int digits)
{
  if (digits < 10)
  {
    lcd.print('0');
  }
  lcd.print(digits);
}