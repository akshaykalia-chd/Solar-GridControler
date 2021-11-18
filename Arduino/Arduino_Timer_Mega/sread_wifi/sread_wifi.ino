void setup() 
{
  Serial.begin(115200);
  // put your setup code here, to run once:

}

void loop() 
{
  SreadWiFiconfig("GETSSID");
  SreadWiFiconfig("GETPASS");
  // put your main code here, to run repeatedly:

}


String SreadWiFiconfig(String sel)
{
  if (sel == "GETSSID")
  {
    Serial.print("Eenter SSID:");
  }
  if (sel == "GETPASS")
  {
    Serial.print("Eenter Password:");
  }
  String input = "";
  char inbyte = ' ';
  while (inbyte != '\n')
  {
    while (Serial.available())
    {
      inbyte = Serial.read();
      if (inbyte != '\n')
      {
        input += inbyte;
      }
    }
  }
  Serial.println(input);
  return input;
}
