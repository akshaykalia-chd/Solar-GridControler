//*******************************************************
//Function to display data on LCD
//*******************************************************
void lcd_Display(byte RelayOn, float KWHMPPT, float ampsMPPT, float amps, float volts, float ampsac, byte PageNo, int OnDay, int OnMonth, int OnHour, int OnMinute, float KWH, unsigned long GridTime, float temperature, byte build)
{
  if (PageNo == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("IM4S SGMC M-1   ");
    lcd.setCursor(0, 1);
    lcd.print("Code Build:");
    lcd.print(build);
    lcd.print("     ");
  }
  if (PageNo == 1)
  {
    digitalClockDisplay();
  }
  if (PageNo == 2)
  {
    lcd.setCursor(0, 0);
    lcd.print("KWH used:");
    lcd.print(ftos(KWH / 3600000000));
    lcd.print("     ");
    lcd.setCursor(0, 1);
    lcd.print("KWH PV:");
    lcd.print(ftos(KWHMPPT / 3600000000));
    lcd.print("       ");
  }
  if (PageNo == 3)
  {
    lcd.setCursor(0, 0);
    int runtime = 100 / amps;
    runtime = runtime * 0.4;
    lcd.print("Run Time(H):");
    if (runtime < 0)
    {
      lcd.print("CHRG");
    }
    lcd.print(ftos(runtime));
    lcd.print("H");
    lcd.print("       ");
    lcd.setCursor(0, 1);
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
    lcd.print("       ");
  }
  if (PageNo == 4)
  {
    lcd.setCursor(0, 0);
    lcd.print("Batt(V):");
    lcd.print(ftos(volts));
    lcd.print("V");
    lcd.print("       ");
    lcd.setCursor(0, 1);
    lcd.print("Batt(A):");
    lcd.print(ftos(amps));
    lcd.print("A");
    lcd.print("       ");
  }

  if (PageNo == 5)
  {
    lcd.setCursor(0, 0);
    lcd.print("PV (A):");
    lcd.print(ftos(ampsMPPT));
    lcd.print("A");
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("Mains(A):");
    lcd.print(ftos(ampsac));
    lcd.print("A");
    lcd.print("         ");

  }
  if (PageNo == 6)
  {
    lcd.setCursor(0, 0);
    lcd.print("TGT(H):");
    lcd.print(ftos(GridTime / 3600000));
    lcd.print("       ");
    lcd.setCursor(0, 1);
    lcd.print("Celsius::");
    lcd.print(temperature);
    lcd.print("            ");
  }
  if (PageNo == 7)
  {
    lcd.setCursor(0, 0);
    lcd.print("On Date:");
    lcd.print(OnDay);
    lcd.print("/");
    lcd.print(OnMonth);
    lcd.print("      ");
    lcd.setCursor(0, 1);
    lcd.print("On Time:");
    lcd.print(OnHour);
    lcd.print(":");
    lcd.print(OnMinute);
    lcd.print("      ");
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


