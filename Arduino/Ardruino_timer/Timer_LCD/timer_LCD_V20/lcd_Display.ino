//*******************************************************
//Function to display data on LCD
//*******************************************************
void lcd_Display(byte RelayOn, float amps, float volts, float ampsac, byte PageNo, int OnDay, int OnMonth, int OnHour, int OnMinute, float KWH, unsigned long GridTime, float CutOffVolts, float CutOffApms, byte SogMorning, byte SogNight, float sysvoltsdc, float SysampsDC, float SysampsAC)
{
  if (PageNo == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("IM4S SSGMC M-3");
    lcd.print("            ");
    lcd.setCursor(0, 1);
    lcd.print("Code Build:16");
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
    lcd.print("TGT(H):");
    lcd.print(GridTime / 3600000);
    lcd.print("           ");
  }
  if (PageNo == 3)
  {
    lcd.setCursor(0, 0);
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
    lcd.setCursor(0, 1);
    lcd.print(volts);
    lcd.print("V");
    lcd.print(" ");
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
    lcd.print("Grid:");
    if (RelayOn == 0)
    {
      lcd.print("Off");
    }
    if (RelayOn == 1)
    {
      lcd.print("On");
    }
    if (RelayOn == 2)
    {
      lcd.print("Timer");
    }
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("On Volts:");
    lcd.print(CutOffVolts);
    lcd.print("         ");
  }
  if (PageNo == 6)
  {
    lcd.setCursor(0, 0);
    lcd.print("Off Amps:");
    lcd.print(CutOffApms);
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("SOG PM(M):");
    lcd.print(SogMorning);
    lcd.print("         ");
  }
  if (PageNo == 7)
  {
    lcd.setCursor(0, 0);
    lcd.print("SOG AM(M):");
    lcd.print(SogNight);
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("Sys Amps DC:");
    lcd.print(SysampsDC * 1024.00);
    lcd.print("         ");
  }
  if (PageNo == 8)
  {
    lcd.setCursor(0, 0);
    lcd.print("Sys Volts DC:");
    lcd.print(sysvoltsdc * 1024.00);
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("Sys Amps AC:");
    lcd.print(SysampsAC * 1024.00);
    lcd.print("         ");
  }
  if (PageNo == 9)
  {
    lcd.setCursor(0, 0);
    lcd.print("On Date:");
    lcd.print(OnDay);
    lcd.print("/");
    lcd.print(OnMonth);
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("On Time:");
    lcd.print(OnHour);
    lcd.print(":");
    lcd.print(OnMinute);
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
  lcd.print("   ");
  printDigits(day());
  lcd.print("/");
  printDigits(month());
  lcd.print("/");
  printDigits(year());
  lcd.print("         ");
  lcd.setCursor(0, 1);
  lcd.print("    ");
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