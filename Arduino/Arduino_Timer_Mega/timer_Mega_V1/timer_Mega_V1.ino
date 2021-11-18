/******************************************************************
Board configuration
This function is used for configuration various board parameters
*****************************************************************/
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // LCD Pin interface

void setup()
{
  lcd.begin(16, 2);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(29, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(115200);
  setSyncProvider(RTC.get);
  setSyncInterval(3600);
  if (button() == "Left")
  {
    sysconfig();
    setSyncProvider(RTC.get);
  }
  if (!RTC.chipPresent())
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RTC Err");
    while (1);
  }
  lcd.setCursor(0, 0);
  lcd.print("  Please Wait:  ");
  lcd.setCursor(0, 1);
  lcd.print("System Rebooting");
  TestEsp8266();
  delay(15000);
  SendCmd("AT+CIPMUX=1\r\n", 10, true);
  SendCmd("AT+CIFSR\r\n", 10, true);
}
/*******************************************************
Main function this will be running in a infinite loop
*******************************************************/

void loop()
{
  int build = 1;
  float KWH = 0;
  float KWHMPPT = 0;
  unsigned long GridTime = 0;
  float bat1volts = 0;
  float bat2volts = 0;
  float bat3volts = 0;
  float bat4volts = 0;
  float volts = 0;
  float temperature = 0;
  float amps = 0;
  float ampsMPPT = 0;
  float ampsac = 0;

  int offsets[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  float calf[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int i = 0;
  int j = 41;
  int k = 61;
  while ( i < 9)
  {
    offsets[i] = readint(j) - 1;
    calf[i] = readFloat(k) - 1;
    j += 2;
    k += 4;
    i++;
  }


  byte datalogset = EEPROM.read(31);

  byte NoOfTimers = EEPROM.read(0);
  int onTime[5] = {0, 0, 0, 0, 0};
  int offTime[5] = {0, 0, 0, 0, 0};
  if (NoOfTimers != 0 && NoOfTimers <= 5)
  {
    for (int i = 0; i < NoOfTimers; i++)
    {
      onTime[i] = get_timer(i, NoOfTimers, "OnTime");
      offTime[i] = get_timer(i, NoOfTimers, "OffTime");
    }
  }

  byte SogMorningb = EEPROM.read(29);
  byte SogNightb =  EEPROM.read(30);

  int OnDay = day();
  int OnMonth = month();
  int OnHour = hour();
  int OnMinute = minute();

  float CutOffVolts = readFloat(21);
  float CutOffApms = readFloat(25);

  int Port = readint(36);
  String Prt = String (Port, DEC);
  String IP = ipconfig("GET");

  byte RelayOn = 0;
  digitalWrite(13, LOW);
  byte RunCount_ARON = 0;
  byte RunCount = 0;

  unsigned long elaptime = 0;
  unsigned long pelaptime = millis();
  unsigned long kwhCheckPoint = millis ();

  byte PageNo = 0;

  String cmd = "AT+CIPSERVER=1,";
  cmd += Prt;
  cmd += "\r\n";
  SendCmd(cmd, 10, true);


  while (1)
  {
    if (button() != "None")
    {
      configlog (datalogset, CutOffVolts, CutOffApms, SogMorningb, SogNightb, NoOfTimers, onTime[0], offTime[0], onTime[1], offTime[1], onTime[2], offTime[2], onTime[3], offTime[3], onTime[4], offTime[4], offsets[0], offsets[1], offsets[2], offsets[3], offsets[4], offsets[5], offsets[6], offsets[7], offsets[8], calf[0], calf[1], calf[2], calf[3], calf[4], calf[5], calf[6], calf[7], calf[8]);
    }
    if (PageNo > 8)
    {
      PageNo = 1;
    }
    lcd_Display(RelayOn, KWHMPPT, ampsMPPT, amps, volts, ampsac, PageNo, OnDay, OnMonth, OnHour, OnMinute, KWH, GridTime, temperature, build);
    bat1volts = parameterVal(calf[0], read_sensor(1, offsets[0], 0));
    bat2volts = parameterVal(calf[1], read_sensor(1, offsets[1], 1));
    bat3volts = parameterVal(calf[2], read_sensor(1, offsets[2], 2));
    bat4volts = parameterVal(calf[3], read_sensor(1, offsets[3], 3));
    volts = parameterVal(calf[4], read_sensor(1, offsets[4], 4));
    temperature = parameterVal(calf[5], read_sensor(1, offsets[5], 5));
    amps = parameterVal(calf[6], read_sensor(1, offsets[6], 6));
    ampsMPPT = parameterVal(calf[7], read_sensor(1, offsets[7], 7));
    ampsac = parameterVal(calf[8], read_sensor(1, offsets[8], 8));

    if (RelayOn == 0)
    {
      pelaptime = millis();
      elaptime = 0;
    }
    if (NoOfTimers == 0)
    {
      RelayOn = activate_relay(volts, CutOffVolts, RelayOn, 0, 0);
      if (RunCount_ARON >= 200)
      {
        RelayOn = deactivate_relay(amps, CutOffApms, SogMorningb, SogNightb, RelayOn, elaptime, 0);
        RunCount_ARON = 0;
      }
    }
    else
    {
      for (int i = 0; i < NoOfTimers; i++)
      {
        RelayOn = activate_relay(volts, CutOffVolts, RelayOn, onTime[i], offTime[i]);
        if (RunCount_ARON >= 200)
        {
          RelayOn = deactivate_relay(amps, CutOffApms, SogMorningb, SogNightb, RelayOn, elaptime, offTime[i]);
          RunCount_ARON = 0;
        }
      }
    }

    GridTime = GridTime + Cal_Gridtime(amps, kwhCheckPoint);
    KWH = KWH + Cal_KWH(amps, kwhCheckPoint, ampsac);
    KWHMPPT = KWHMPPT + Cal_KWHMPPT(volts, kwhCheckPoint, ampsMPPT);
    kwhCheckPoint = millis();
    if (GridTime > 4294966296)
    {
      GridTime = 0;
      KWH = 0;
      OnDay = day();
      OnMonth = month();
      OnHour = hour();
      OnMinute = minute();
    }
    if (RelayOn != 0)
    {
      elaptime = millis() - pelaptime;
      RunCount_ARON++;
    }
    if (RunCount > 25)
    {
      datalog(datalogset, IP, Prt, RelayOn, amps, volts, bat1volts,  bat2volts,  bat3volts,  bat4volts,  ampsac, OnDay, OnMonth, OnHour, OnMinute, KWH, GridTime, KWHMPPT, ampsMPPT, temperature, build);
      RunCount = 0;
    }

    if (RunCount > 10 && RunCount % 10 == 0)
    {
      PageNo++;
    }
    RunCount++;
  }
}










