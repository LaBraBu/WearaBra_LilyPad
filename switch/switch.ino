void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);  // ローインピーダンス
}

void loop()
{
  if (digitalRead(2) == LOW)
  {
    Serial.println("off");
    digitalWrite(13, LOW);  // 消灯
  }
  else
  {
    Serial.println("on");
    digitalWrite(13, HIGH);  // 点灯
  }
  delay(300);
}

