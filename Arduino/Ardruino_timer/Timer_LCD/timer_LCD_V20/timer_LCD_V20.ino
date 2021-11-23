#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // LCD Pin interface
//*******************************************//
//Board configuration 
//This function is used for configuration various board parameters
//Do not modify
//*******************************************//
void setup() 
{
  pinMode(13, OUTPUT);             // initialize digital pin 13 as an output.
  analogReference(DEFAULT);        // initialize analog Reference voltage to 5v 
  lcd.begin(16, 2);
  Serial.begin(9600);              // initialize serial communication at 9600 bits per second:
  setSyncProvider(RTC.get);    // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
    {
     int err=1;
      while (err !=0)
      {
        lcd.print("RTC Err");
        delay(2000);
        lcd.clear();
      }
     }
Serial.println("Date,Time,On Time,Battery Voltage,Relay Status");      
}
//*******************************************************
//Main function this will be running in a infinite loop 
//Do not modify unless explicitly defined by a comment
//*******************************************************
void loop() 
{
  float volts = avg_voltage();
  float amps =  avg_current();
  lcd_Display(amps,volts,"off");  
  set_time();
}

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
return;  
}

//*******************************************************
//Reading Voltage and avraging over 4 second interval 
//Do not modify unless explicitly defined by a comment
//*******************************************************
float avg_voltage()
{
  float voltage = 0; 
  int RunCount = 0;
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  while (currentMillis-previousMillis < 1000)
  {	
    currentMillis = millis();
    int sensorValue1 = analogRead(A2);                   // read the input on analog pin 1(Voltage to measure)
    delay(10);
    float voltage1 = bat_v(sensorValue1);                // calculating 60v equivalent
    voltage = voltage + voltage1;
    RunCount = RunCount + 1;
  }
voltage = voltage/RunCount;
return voltage;
}

//*******************************************************
//Reading Current and avraging over 1 second interval 
//Do not modify unless explicitly defined by a comment
//*******************************************************
float avg_current()
{
  float current = 0; 
  int RunCount = 0;
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  while (currentMillis-previousMillis < 1000)
  {	
    currentMillis = millis();
    int sensorValue1 = analogRead(A1);                   // read the input on analog pin 1(Voltage to measure)
    delay(10);
    sensorValue1 = sensorValue1 - 509; 
    float current1 = bat_c(sensorValue1);                // calculating 60v equivalent
    current = current + current1;
    RunCount = RunCount + 1;
  }
current = current/RunCount;
return current;
}

//*******************************************************
//Functions to calculate 60v equivalent and 30AMP
//Do not modify unless explicitly defined by a comment
//*******************************************************
float bat_v (int x)
{
  float ret_bat = x * (60/1023.00);
  return ret_bat;
}

float bat_c (int x)
{
  float ret_c = x * (30/1023.00);
  return ret_c;
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

//*******************************************************
// Function to set time 
//Do not modify unless explicitly defined by a comment
//*******************************************************
void set_time()
{ 
  int Hour, Min, Sec,Day, Year,Month;
  Hour = hour();
  Min = minute();
  Sec = second();
  Day = day();
  Month = month();  
  Year = year();
  while (button()!= "Select")
  {
    lcd.setCursor(0,0);
    lcd.print("Hour:");
    lcd.print(Hour);
    lcd.print("   ");
    if(Hour < 23)
    {
      if (button() == "Up")
      {
        Hour++;
      }
      if (button() == "Down")
      {
        Hour--;
      }
    }
    if(Hour = 23)
    {
      if (button() == "Up")
      {
        Hour = 0;
      }
      if (button() == "Down")
      {
        Hour--;
      }
    }
   }
update_rtc(Hour, Min, Sec,Day, Year,Month);  
return;
}

void update_rtc(int Hour, int Min, int Sec, int Day, int Year, int Month)
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
  lcd.print("RTC updated");
}

String button()
{
int sensorValue0 = analogRead(A0);                   
  if (sensorValue0 < 5)
  return ("Right");
  if (sensorValue0 > 95 && sensorValue0 <= 100)
  return ("Up");
  if (sensorValue0 > 250 && sensorValue0 <= 255)  
  return ("Down");
  if (sensorValue0 > 404 && sensorValue0 <= 408)  
  return ("Left");
  if (sensorValue0 > 635 && sensorValue0 <= 640)  
  return ("Select");
return ("None");
}

//*******************************************************
//Function to activate relay
//Do not modify unless explicitly defined by a comment
//*******************************************************
boolean activate_relay(boolean RelayStatus,float voltage) //Function to activate relay
{
  if (RelayStatus == true)
  {
   digitalWrite(13, LOW);   // turn the LED/Relay off by making the voltage LOW
   boolean RelayOn = false;
   return RelayOn;   
  }
  else 
  {
     boolean RelayOn = false; 
     if (voltage < 43.55)
       {
         digitalWrite(13, HIGH);   // turn the LED/Relay on by making the voltage high
         boolean RelayOn = true; 
         return RelayOn;
       }
     else
       {
       return RelayOn;
       }
   }
}

//*******************************************************
//Function to print data on usb
//Do not modify unless explicitly defined by a comment
//*******************************************************
void displaydata(unsigned long DelayTimeInMin,float BatVolts, boolean RelayStatus, char CalledBy,unsigned long SdtimeM) //function to print data on usb
{
  //digitalClockDisplay();
  Serial.print(DelayTimeInMin);
  Serial.print(" Minutes");
  Serial.print(",");
  Serial.print(BatVolts);
  Serial.print(" Volts");
  Serial.print(",");
  if(RelayStatus == true)
  {
    if (CalledBy == 'P')
    {
      Serial.print("Relay On by Alarm");
    }
    else
    {
      Serial.print("Relay On");
    }
  }
  else
  {
    Serial.print("Relay Off");
  }
  if (hour()>=07 && hour()<=16)
  {
    Serial.print(",");
    Serial.print("Varialble On time is currently disabled. The Pot is currently set to ");
    Serial.print(SdtimeM);
    Serial.print(" Minutes");
   }
  Serial.println();
 return;   
}

//*******************************************************
//This will run on every alarm trigger 
//Do not modify unless explicitly defined by a comment
//*******************************************************
void Alarm(int onTime,int offTime)
{
  int HH,MM,cTime;
  HH=hour();
  MM=minute();
  cTime=HH*100;
  cTime=cTime+MM;
    if(cTime >= onTime && cTime <= offTime)
    { 
      while(cTime != offTime)
        {
          digitalWrite(13, HIGH);   // turn the LED/Relay on by making the voltage high
          boolean relay_on = true;
          float voltage=avg_voltage(); 
          //displaydata(offTime,voltage, relay_on, 'P',0);
          HH=hour();
          MM=minute();
          cTime=HH*100;
          cTime=cTime+MM;
        }      
      digitalWrite(13, LOW);   // turn the LED/Relay off by making the voltage low      
    }
    if(cTime >= onTime && offTime <= onTime)
    {
      while(cTime != offTime)
        {
          digitalWrite(13, HIGH);   // turn the LED/Relay on by making the voltage high
          boolean relay_on = true;
          float voltage=avg_voltage(); 
          //displaydata(offTime,voltage, relay_on, 'P',0);
          HH=hour();
          MM=minute();
          cTime=HH*100;
          cTime=cTime+MM;
        }
      digitalWrite(13, LOW);   // turn the LED/Relay off by making the voltage low      
     }
return;  
}
