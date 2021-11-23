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
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(115200);
  setSyncProvider(RTC.get);
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
  TestEsp8266();
  SendCmd("AT+CIPMUX=1", false, 1);
}
/*******************************************************
Main function this will be running in a infinite loop
*******************************************************/

void loop()
{
  float KWH = 0;
  float KWHMPPT = 0;
  unsigned long GridTime = 0;
  float volts = 0;
  float amps = 0;
  float ampsMPPT = 0;
  float ampsac = 0;
  byte PageNo = 1;
  byte PPageNo = 1;

  byte datalogset = EEPROM.read(29);

  byte NoOfTimers = 0;
  NoOfTimers = EEPROM.read(0);

  float CutOffApms = EEPROM.read(26) / 100.00;
  CutOffApms = CutOffApms + EEPROM.read(25);

  float CutOffVolts = EEPROM.read(24) / 100.00;
  CutOffVolts = CutOffVolts + EEPROM.read(23);

  byte SogMorningb = EEPROM.read(27);
  byte SogNightb =  EEPROM.read(28);

  float sysvoltsdc = EEPROM.read(21) / 1024.00;

  int OnDay = day();
  int OnMonth = month();
  int OnHour = hour();
  int OnMinute = minute();
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

  float SysampsDC = EEPROM.read(22) / 1024.00;
  float DCcalf = EEPROM.read(40) / 100.00;
  DCcalf = DCcalf + EEPROM.read(39);

  int DcOffset = read_4DitiNo(31, 32);
  float SysampsAC = EEPROM.read(30) / 1024.00;

  float ACcalf = EEPROM.read(42) / 100.00;
  ACcalf = ACcalf + EEPROM.read(41);

  int ACOffset = read_4DitiNo(33, 34);
  byte ACerror = EEPROM.read(43);

  int Port = read_4DitiNo(35, 36);
  String Prt = String (Port, DEC);
  String IP = ipconfig("GET");

  byte RelayOn = 0;
  digitalWrite(13, LOW);
  byte RunCount = 0;

  unsigned long elaptime = 0;
  unsigned long pelaptime = millis();
  unsigned long previousMillis = millis ();

  ConnectServer("UDP", IP , Prt);
  while (1)
  {
    PageNo = update_btn(button(), PageNo, 11, 150);
    volts = avg_voltage(sysvoltsdc);
    PageNo = update_btn(button(), PageNo, 11, 150);
    amps = avg_currentDc(SysampsDC, DCcalf, DcOffset);
    PageNo = update_btn(button(), PageNo, 11, 150);
    ampsMPPT = avg_currentMPPT(SysampsDC, DCcalf, DcOffset);
    PageNo = update_btn(button(), PageNo, 11, 150);
    ampsac = avg_currentAc(SysampsAC, ACcalf, ACOffset, ACerror);
    PageNo = update_btn(button(), PageNo, 11, 150);
    if (RelayOn == 0)
    {
      pelaptime = millis();
      elaptime = 0;
    }
    if (NoOfTimers == 0)
    {
      RelayOn = activate_relay(volts, CutOffVolts, RelayOn, 0, 0);
      PageNo = update_btn(button(), PageNo, 11, 150);
      if (RunCount >= 100)
      {
        RelayOn = deactivate_relay(amps, CutOffApms, SogMorningb, SogNightb, RelayOn, elaptime, 0);
      }
    }
    for (int i = 0; i < NoOfTimers; i++)
    {
      RelayOn = activate_relay(volts, CutOffVolts, RelayOn, onTime[i], offTime[i]);
      PageNo = update_btn(button(), PageNo, 11, 150);
      if (RunCount >= 100)
      {
        RelayOn = deactivate_relay(amps, CutOffApms, SogMorningb, SogNightb, RelayOn, elaptime, offTime[i]);
      }
    }
    if (RunCount >= 100)
    {
      RunCount = 0;
    }
    GridTime = GridTime + Cal_Gridtime(amps, previousMillis);
    KWH = KWH + Cal_KWH(amps, previousMillis, ampsac);
    KWHMPPT = KWHMPPT + Cal_KWHMPPT(volts, previousMillis, ampsMPPT);
    previousMillis = millis();
    PageNo = update_btn(button(), PageNo, 11, 150);
    if (PageNo != PPageNo)
    {
      lcd.clear();
      PPageNo = PageNo;
    }
    lcd_Display(RelayOn, KWHMPPT, ampsMPPT, amps, volts, ampsac, PageNo, OnDay, OnMonth, OnHour, OnMinute, KWH, GridTime, CutOffVolts, CutOffApms, SogMorningb, SogNightb, sysvoltsdc, SysampsDC, SysampsAC);
    datalog(datalogset, RelayOn, amps, volts, ampsac, OnDay, OnMonth, OnHour, OnMinute, KWH, GridTime, KWHMPPT, ampsMPPT, CutOffVolts, CutOffApms, SogMorningb, SogNightb, sysvoltsdc, SysampsDC, SysampsAC, ACOffset, DcOffset, ACcalf, DCcalf, ACerror, NoOfTimers, onTime[0], offTime[0], onTime[1], offTime[1], onTime[2], offTime[2], onTime[3], offTime[3], onTime[4], offTime[4]);
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
      RunCount++;
    }
  }
}










