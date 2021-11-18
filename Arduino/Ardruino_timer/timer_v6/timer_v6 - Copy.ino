#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
//*******************************************//
//Board configuration 
//This function is used for configuration various board parameters
//Do not modify
//*******************************************//
void setup() 
{
  pinMode(13, OUTPUT);             // initialize digital pin 13 as an output.
  pinMode(11, OUTPUT);             // initialize digital pin 11 as an output.
  pinMode(10, INPUT);              // initialize digital pin 10 as an input.
  analogReference(DEFAULT);        // initialize analog Reference voltage to 5v 
  digitalWrite(11, HIGH);          // initialize digital pin 11 to High.
  int time_set= digitalRead(10);   // Reading Time Set Switch
  Serial.begin(9600);              // initialize serial communication at 9600 bits per second:
  if (time_set == 1)
  {
    set_time();
  }
  setSyncProvider(RTC.get);    // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
    {
     Serial.println("Unable to sync with the RTC");
    }
  else
    {
      Serial.println("RTC has set the system time");      
    }
  Serial.println("Date,Time,On Time,Battery Voltage,Relay Status");      
 }
//*******************************************************
//Main function this will be running in a infinite loop 
//Do not modify unless explicitly defined by a comment
//*******************************************************
void loop() 
{
  int sensorValue0 = 0;
  unsigned long dtimeM = 0;
  unsigned long dtimem = 0;
  float voltage = 0;
  boolean RelayOn = false;
  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;
  unsigned long SdtimeM = 0;
  sensorValue0 = analogRead(A0);                   // read the input on analog pin 0 (Time delay selection pot)
  dtimeM = cal_wait(sensorValue0,'M');             // calculating delay time in Minutes
  dtimem = cal_wait(sensorValue0,'m');             // calculating delay time in Mili seconds 
  if (hour()>=07 && hour()<=16)
  {
    SdtimeM = dtimeM;
    dtimeM = 15;   
    dtimem = 15*60*100;
  }
  voltage = avg_voltage();                       // record battery voltage
  RelayOn = activate_relay(false,voltage);     // function to activate_relay. When called with “false” and “input voltage” it will check the voltage (Relay set if voltage less than threshold) and if relay turns ON will return true else it will return false
  displaydata(dtimeM,voltage,RelayOn,'o',SdtimeM);          // Data Log on USB
  Alarm(1800,2030);                                       // 6:00pm every day (xxxx,xxxx) values denoted by x can be modified to change trigger time (On time is hours for example 1800 for 6:00PM  ,off time in hours example 2030 for 8:30PM)
  currentMillis = millis();
  previousMillis = currentMillis;
  while (RelayOn == true)
  {
    currentMillis = millis();
    if (currentMillis-previousMillis < dtimem)
    {
      voltage = avg_voltage();                   // record battery voltage
      displaydata(dtimeM,voltage,RelayOn,'o',SdtimeM);         // Data Log on USB
    }
    else
    {
       RelayOn = activate_relay(true,voltage);         // function activate_relay when called with “true” will set the relay off and will return false
    }  
  }
}

//*******************************************************
//Alarm Function to trigger relay at specific times 
//Do not modify unless explicitly defined by a comment
//*******************************************************
void Alarm(int OnTime,int OffTime)
{
  int cHs = hour();
  int cMs = minute();
  int cTime =cHs*100;
  cTime = cTime + cMs;
  if (cTime>=OnTime && cTime<OffTime)
    {
      float HDtime=OffTime-cTime;
        if (HDtime<100)
          {
          int Dtime=HDtime;
          preset(Dtime);
          return;
          }
        else
          {
          HDtime = HDtime/100;
          int Dtime = HDtime*60;
          preset(Dtime);
          return;
          }
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
  while (currentMillis-previousMillis < 4000)
  {	
    currentMillis = millis();
    int sensorValue1 = analogRead(A1);                   // read the input on analog pin 1(Voltage to measure)
    float voltage1 = bat_v(sensorValue1);                // calculating 60v equivalent
    voltage = voltage + voltage1;
    RunCount = RunCount + 1;
  }
voltage = voltage/RunCount;
return voltage;
}
//*******************************************************
//This will run on every alarm trigger 
//Do not modify unless explicitly defined by a comment
//*******************************************************
void preset(int Dtime)
{
  unsigned long dtimeM = Dtime; 
  digitalWrite(13, HIGH);  // turn the LED/Relay on (HIGH is the voltage level)  
  boolean relay_on = true;
  unsigned long dtime = dtimeM * 60000;
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  while (relay_on == true)
    {
      float voltage=avg_voltage(); 
      unsigned long currentMillis = millis();
      if (currentMillis-previousMillis < dtime)
      {
       displaydata(dtimeM,voltage, relay_on, 'P',0);
      }
      else
      {
       digitalWrite(13, LOW);   // turn the LED/Relay off by making the voltage LOW
       relay_on = false;
      }  
    }
  return;
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
         digitalWrite(13, HIGH);   // turn the LED/Relay off by making the voltage LOW
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
  digitalClockDisplay();
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
//Function to calculate 60v equivalent 
//Do not modify unless explicitly defined by a comment
//*******************************************************
float bat_v (int x)
{
  float ret_bat = x * (60/1023.00);
  return ret_bat;
}
//*******************************************************
//Function to display date and time
//Do not modify unless explicitly defined by a comment
//*******************************************************
void digitalClockDisplay() // digital clock display of the time
{
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(year()); 
  Serial.print(",");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(",");
}
//*******************************************************
// utility function prints preceding colon and leading 0 for date and time
//Do not modify unless explicitly defined by a comment
//*******************************************************
void printDigits(int digits) 
{
  Serial.print(":");
  if(digits < 10)
  {
    Serial.print('0');
  }
  Serial.print(digits);
}
//****************************************************
//Function to set time
//****************************************************
void set_time()
{
  Serial.println("*******************************************************************************************");
  Serial.println("**  Time Set Mode Active To exit this mode flip the time set switch to normal position   **");
  Serial.println("**  To exit this mode flip the time set switch to normal position                        **");
  Serial.println("**  The System will reboot/reset to Time Set when time set switch is ON                  **");
  Serial.println("*******************************************************************************************");
  tmElements_t tm;
  int Hour, Min, Sec;
  int Day, Year,Month;
  Serial.print("Enter current Hours (00-24): ");
  while(Serial.available() == 0){}
  Hour=Serial.parseInt();
  Serial.print(Hour);
  Serial.println();
  Serial.print("Enter current Minutes(00-60): ");
  while(Serial.available() == 0){}
  Min=Serial.parseInt();
  Serial.print(Min);
  Serial.println();
  Serial.print("Enter current Seconds(00-60): ");
  while(Serial.available() == 0){}
  Sec=Serial.parseInt();
  Serial.print(Sec);
  Serial.println();
  Serial.print("Enter current Day(00-31): ");
  while(Serial.available() == 0){}
  Day=Serial.parseInt();
  Serial.print(Day);
  Serial.println();
  Serial.print("Enter current Month(01-12): ");
  while(Serial.available() == 0){}
  Month=Serial.parseInt();
  Serial.print(Month);
  Serial.println();
  Serial.print("Enter current Year(2014): ");
  while(Serial.available() == 0){}
  Year=Serial.parseInt();
  Serial.print(Year);
  Serial.println();
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  tm.Day = Day;
  tm.Month = Month;
  tm.Year = CalendarYrToTm(Year);
  RTC.write(tm);
  Serial.println("DS1307 configured");
  return;
}    
//*******************************************************
//function to calculate wait time based on pot position
//Do not modify unless explicitly defined by a comment
//*******************************************************
unsigned long cal_wait(int x,char y) //function to calculate wait time based on pot position
{ 	
  if (x >=0&&x<=63)
  {     
	if (y=='M')
	{
        return 15;
	}
        else if (y=='m')
	{
        return 900000;                
	}
  }  
  else if (x >=64&&x<=127)
  {
        if (y=='M')
	{
        return 30;
	}
        else if (y=='m')
	{
        return 1800000;                
	}
  }
  else if (x>=128&&x<=191)
  {
        if (y=='M')
	{
        return 45;
	}
        else if (y=='m')
	{
        return 2700000;                
	}
  }
  else if (x>=192&&x<=255)
  {
        if (y=='M')
	{
        return 60;
	}
        else if (y=='m')
	{
        return 3600000;                
	}
  }
  else if (x>=256&&x<=319)
  {
        if (y=='M')
	{
        return 75;
	}
        else if (y=='m')
	{
        return 4500000;                
	}
  }
  else if (x>=320&&x<=383)
  {
        if (y=='M')
	{
        return 90;
	}
        else if (y=='m')
	{
        return 5400000;                
	}
  }
  else if (x>=384&&x<=447)
  {
        if (y=='M')
	{
        return 105;
	}
        else if (y=='m')
	{
        return 6300000;                
	}
  }
  else if (x>=448&&x<=511)
  {
        if (y=='M')
	{
        return 120;
	}
        else if (y=='m')
	{
        return 7200000;                
	}
  }
  else if (x>=512&&x<=575)
  {
        if (y=='M')
	{
        return 135;
	}
        else if (y=='m')
	{
        return 8100000;                
	}
  }
  else if (x>=576&&x<=639)
  {
        if (y=='M')
	{
        return 150;
	}
        else if (y=='m')
	{
        return 9000000;                
	}
  }
  else if (x>=640&&x<=703)
  {
        if (y=='M')
	{
        return 165;
	}
        else if (y=='m')
	{
        return 9900000;                
	}
  }
  else if (x>=704&&x<=767)
  {
        if (y=='M')
	{
        return 180;
	}
        else if (y=='m')
	{
        return 10800000;                
	}
  }
  else if (x>=768&&x<=831)
  {
        if (y=='M')
	{
        return 195;
	}
        else if (y=='m')
	{
        return 11700000;                
	}
  }
  else if (x>=832&&x<=895)
  {
        if (y=='M')
	{
        return 210;
	}
        else if (y=='m')
	{
        return 12600000;                
	}
  }
  else if (x>=896&&x<=959)
  {
        if (y=='M')
	{
        return 225;
	}
        else if (y=='m')
	{
        return 13500000;                
	}
  }
  else if (x>=960&&x<=1023)
  {
        if (y=='M')
	{
        return 240;
	}
        else if (y=='m')
	{
        return 14400000;                
	}
  }
return 0;
}
