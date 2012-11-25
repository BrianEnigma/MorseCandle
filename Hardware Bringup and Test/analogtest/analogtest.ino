const int ANALOG_PIN = 10;
const int DIGITAL_PIN = 13;

void setup()   
{
  pinMode(ANALOG_PIN, OUTPUT);
  pinMode(DIGITAL_PIN, OUTPUT);
}

void loop()
{
  analogWrite(ANALOG_PIN, 255);
  digitalWrite(DIGITAL_PIN, HIGH);
  delay(1000);
  analogWrite(ANALOG_PIN, 128);
  digitalWrite(DIGITAL_PIN, LOW);
  delay(1000);
}
