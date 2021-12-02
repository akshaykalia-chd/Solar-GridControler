#define DEBUG true
void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200); // your esp's baud rate might be different
  sendData("AT+RST\r\n", 2000, DEBUG); // reset module
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); // configure as access point
  sendData("AT+CWJAP=\"IM4s_Wi_Fi_M4\",\"some_pass\"\r\n", 10000, DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n", 1000, DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // turn on server on port 80
}

void loop()
{

  if (Serial1.find("+IPD,"))
  {
    delay(1000);

    int connectionId = Serial1.read() - 48; // subtract 48 because the read() function returns
    // the ASCII decimal value and 0 (the first decimal number) starts at 48

    String webpage = "<h1>Hello</h1>&lth2>World!</h2><button>LED1</button>";

    String cipSend = "AT+CIPSEND=";
    cipSend += connectionId;
    cipSend += ",";
    cipSend += webpage.length();
    cipSend += "\r\n";

    sendData(cipSend, 1000, DEBUG);
    sendData(webpage, 1000, DEBUG);

    webpage = "<button>LED2</button>";

    cipSend = "AT+CIPSEND=";
    cipSend += connectionId;
    cipSend += ",";
    cipSend += webpage.length();
    cipSend += "\r\n";

    sendData(cipSend, 1000, DEBUG);
    sendData(webpage, 1000, DEBUG);

    String closeCommand = "AT+CIPCLOSE=";
    closeCommand += connectionId; // append connection id
    closeCommand += "\r\n";

    sendData(closeCommand, 3000, DEBUG);
  }
}

String sendData(String command, const int timeout, boolean debug)
{
  String response = "";

  Serial1.print(command); // send the read character to the Serial1
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial1.available())
    {

      // The esp has data so display its output to the serial window
      char c = Serial1.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}
