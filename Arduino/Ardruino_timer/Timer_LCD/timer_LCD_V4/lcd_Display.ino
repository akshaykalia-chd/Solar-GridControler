//*******************************************************
//Function to display data on LCD
//*******************************************************
void lcd_Display(float amps,float volts,String Rstate,unsigned int GridTime,float ampsac)
{
  if(button() == "Select")
   {
     lcd.setCursor(0,0);
     lcd.print("KWH,A:");
     lcd.print(KWH);
     lcd.print(",");
     lcd.print(ampsac);
     lcd.print("            ");
     lcd.setCursor(0,1);
     lcd.print("24H TGT(M):");
     lcd.print(GridTime);
     lcd.print("        ");
   } 
  if (button() == "None")
  {
    digitalClockDisplay(0,0);
    lcd.setCursor(0,1);
    lcd.print(volts);
    lcd.print("V");
    lcd.print(" "); 
    lcd.print(amps);
    lcd.print("A");  
    lcd.print("     "); 
  }
  if (button() == "Right")
  {
    float runtime = 100/amps;
    runtime = runtime * 0.7;
    lcd.setCursor(0,0);
    lcd.print("Run Time(H):"); 
    lcd.print(runtime);
    lcd.print("         ");
    lcd.setCursor(0,1);
    lcd.print("Grid Supply:"); 
    lcd.print(Rstate);
    lcd.print("         ");
  }
  if (button() == "Left")
  {
    lcd.setCursor(0,0);
    lcd.print("Off Amps:"); 
    lcd.print(EEPROM.read(25));
    lcd.print(".");
    lcd.print(EEPROM.read(26));
    lcd.print("         ");
    lcd.setCursor(0,1);
    lcd.print("Off Volts:"); 
    lcd.print(EEPROM.read(23));
    lcd.print(".");
    lcd.print(EEPROM.read(24));
    lcd.print("         ");
  }
  if (button() == "Up")
  {
    lcd.setCursor(0,0);
    lcd.print("SOG AM(M):"); 
    lcd.print(EEPROM.read(27));
    lcd.print("         ");
    lcd.setCursor(0,1);
    lcd.print("SOG PM(M):");
    lcd.print(EEPROM.read(28)); 
    lcd.print("         ");
  }
  if (button() == "Down")
  {
    lcd.setCursor(0,0);
    lcd.print("System Volts:"); 
    lcd.print(EEPROM.read(21));
    lcd.print("         ");
    lcd.setCursor(0,1);
    lcd.print("System Amps:");
    lcd.print(EEPROM.read(22)); 
    lcd.print("         ");
  }
}
//*******************************************************
//Function to display date and time
//Do not modify unless explicitly defined by a comment
//*******************************************************
void digitalClockDisplay(int CN,int LN) // digital clock display of the time
{
  lcd.setCursor(CN,LN);
  printDigits(hour());
  lcd.print(":");
  printDigits(minute());
  lcd.print(" ");
  printDigits(day());
  lcd.print("/");
  printDigits(month());
  lcd.print("/");
  printDigits(year());  
}
//*******************************************************
// utility function prints preceding colon and leading 0 for date and time
//Do not modify unless explicitly defined by a comment
//*******************************************************
void printDigits(int digits) 
{
  if(digits < 10)
  {
    lcd.print('0');
  }
  lcd.print(digits);
}


