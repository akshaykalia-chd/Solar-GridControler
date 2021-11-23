//*******************************************************
//Functions to set time 
//*******************************************************
void set_time()
{ 
  unsigned int Hour, Min, Sec,Day, Year,Month;
  Hour = hour();
  Min = minute();
  Sec = second();
  Day = day();
  Month = month();  
  Year = year();
  Hour = update_Tcom("Hour",Hour,24);
  update_rtc(Hour, Min, Sec,Day, Year,Month,"Hour");
  Min = update_Tcom("Minute",Min,60);
  update_rtc(Hour, Min, Sec,Day, Year,Month,"Minute");
  Sec = update_Tcom("Seconds",Sec,60);
  update_rtc(Hour, Min, Sec,Day, Year,Month,"Seconds");       
  Day = update_Tcom("Day",Day,32);
  update_rtc(Hour, Min, Sec,Day, Year,Month,"Day");       
  Month = update_Tcom("Month",Month,13);  
  update_rtc(Hour, Min, Sec,Day, Year,Month,"Month");       
  Year = update_Tcom("Year",Year,9999);
  update_rtc(Hour, Min, Sec,Day, Year,Month,"Year");
  lcd.setCursor(0,1);
  lcd.print("Time set");
  lcd.print("     ");
  delay(500);
  lcd.clear();  
  return;
}

void update_rtc(int Hour, int Min, int Sec, int Day, int Year, int Month, String val)
{
  tmElements_t tm;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  tm.Day = Day;
  tm.Month = Month;
  tm.Year = CalendarYrToTm(Year);
  RTC.write(tm);
  lcd.setCursor(0,1);
  lcd.print (val);
  lcd.print(" updated");
  lcd.print("   ");
  delay(500);
  lcd.clear();
}

int update_Tcom(String Tcom, unsigned int Tcom_value, int Tcom_valmax)
{
  while (button()!= "Select")
  { 
    lcd.setCursor(0,0);
    lcd.print(Tcom);
    lcd.print(":");
    lcd.print(Tcom_value);
    lcd.print("          ");
    Tcom_value = update_btn(button(),Tcom_value,Tcom_valmax,250);
  }
  delay (250);      
  return Tcom_value;
}


