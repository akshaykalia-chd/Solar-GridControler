void setup() 
{
  Serial.begin(115200);
  float a = 3000.45;
  float b = 56.33/a;
  String Stra = ftos(a);
  Stra += ",";
  Stra += ftos(b);
  Serial.println(Stra);
}

void loop() 
{
}
String ftos (float a)
{
  String y ="";
  int PD = a; 
  y += PD;
  float temp = a - PD; 
  int AD = temp*100; 
  if ( AD < 10)
  {
    y +=".0";
    y += AD;
    return y;
  }
  y +='.';
  y += AD;
  return y;
}
