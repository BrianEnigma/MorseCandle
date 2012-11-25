const int ANALOG_PIN = 10;

void setup()   
{
  pinMode(ANALOG_PIN, OUTPUT);
}

void loop()
{
  analogWrite(ANALOG_PIN, random(5) * 10 + 78);
  delay(random(90) + 10);
}
