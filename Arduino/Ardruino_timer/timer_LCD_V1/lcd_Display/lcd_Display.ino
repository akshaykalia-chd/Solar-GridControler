#include <LiquidCrystal.h>
#include <Time.h>
#include <DS1307RTC.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // LCD Pin interface
//*******************************************************
//Function to display data on LCD
//Do not modify unless explicitly defined by a comment
//*******************************************************
void lcd_Display(float amps,float volts,String Rstate)
{
  digitalClockDisplay(0,0);
  lcd.setCursor(0,1);
  lcd.print(volts);
  lcd.print("V");
  lcd.print(" "); 
  lcd.print(amps);
  lcd.print("A");  
  lcd.print("     "); 
  if (button() == "Right")
  {
    lcd.setCursor(0,1);
    lcd.print("Relay:"); 
    lcd.print(Rstate);
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

