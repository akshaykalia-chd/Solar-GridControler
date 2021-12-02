void sysconfig()
{
  String term = "Run";
  byte sel = 0;
  while (term != "Exit")
  {
    switch (sel)
    {
      case 0:
        update_sel("Set Time        ");
        sel = update_btn(button(), sel, 8, 250);
        if (button() == "Select")
        {
          delay (250);
          set_time();
        }
        break;
      case 1:
        update_sel("Setup Timers    ");
        sel = update_btn(button(), sel, 8, 250);
        if (button() == "Select")
        {
          delay (250);
          setup_timers();
        }
        break;
      case 2:
        update_sel("CutOffs         ");
        sel = update_btn(button(), sel, 8, 250);
        if (button() == "Select")
        {
          delay (250);
          set_cutoffvolts();
          delay (250);
          set_cutoffamps();
          delay (250);
          lcd.setCursor(0, 0);
          lcd.print("                ");
          lcd.setCursor(0, 1);
          lcd.print("                ");
        }
        break;
      case 3:
        update_sel("SOG Time        ");
        sel = update_btn(button(), sel, 8, 250);
        if (button() == "Select")
        {
          delay (250);
          set_sog();
        }
        break;
      case 4:
        update_sel("Data Logging    ");
        sel = update_btn(button(), sel, 8, 250);
        if (button() == "Select")
        {
          delay (250);
          set_loger();
        }
        break;
      case 5:
        update_sel("Control Station ");
        sel = update_btn(button(), sel, 8, 250);
        if (button() == "Select")
        {
          delay (250);
          ipconfig("SET");
          set_port();
          lcd.setCursor(0, 0);
          lcd.print("                ");
          lcd.setCursor(0, 1);
          lcd.print("                ");
        }
        break;
      case 6:
        update_sel("Calibrate/WiFi  ");
        sel = update_btn(button(), sel, 8, 250);
        if (button() == "Select")
        {
          delay (250);
          lcd.setCursor(0, 1);
          lcd.print("Connect to PC");
          calibrate();
        }
        break;

      case 7:
        update_sel("Exit            ");
        sel = update_btn(button(), sel, 8, 250);
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
}

