void sysconfig()
{
  String term = "Run";
  byte sel = 0;
  while (term != "Exit")
  {
    switch (sel)
    {
      case 0:
        update_sel("Set Time");
        sel = update_btn(button(), sel, 9, 250);
        if (button() == "Select")
        {
          delay (250);
          set_time();
        }
        break;
      case 1:
        update_sel("Setup Timers");
        sel = update_btn(button(), sel, 9, 250);
        if (button() == "Select")
        {
          delay (250);
          setup_timers();
        }
        break;
      case 2:
        update_sel("System Parameter");
        sel = update_btn(button(), sel, 9, 250);
        if (button() == "Select")
        {
          delay (250);
          set_sysvolts();
          set_sysamps();
          set_sysamps_AC();
          set_DcOffset();
          set_AcOffset();
          set_DcCal();
          set_AcCal();
          set_Aacnl();
        }
        break;
      case 3:
        update_sel("Cut Offs");
        sel = update_btn(button(), sel, 9, 250);
        if (button() == "Select")
        {
          delay (250);
          set_cutoffvolts();
          set_cutoffamps();
        }
        break;
      case 4:
        update_sel("SOG Time");
        sel = update_btn(button(), sel, 9, 250);
        if (button() == "Select")
        {
          delay (250);
          set_sog();
        }
        break;
      case 5:
        update_sel("Data Logging");
        sel = update_btn(button(), sel, 9, 250);
        if (button() == "Select")
        {
          delay (250);
          set_loger();
        }
        break;
      case 6:
        update_sel("Wifi ");
        sel = update_btn(button(), sel, 9, 250);
        if (button() == "Select")
        {
          delay (250);
          //wificonfig("SET");
          //SetupEsp8266();

        }
        break;
      case 7:
        update_sel("Control Station");
        sel = update_btn(button(), sel, 9, 250);
        if (button() == "Select")
        {
          delay (250);
          ipconfig("SET");
          set_port();
        }
        break;

      case 8:
        update_sel("Exit");
        sel = update_btn(button(), sel, 9, 250);
        if (button() == "Select")
        {
          term = "Exit";
        }
        break;
    }
  }
}

void update_sel(String comp)
{
  lcd.setCursor(0, 0);
  lcd.print(comp);
  lcd.print("          ");
  lcd.setCursor(0, 1);
  lcd.print("              ");
}

