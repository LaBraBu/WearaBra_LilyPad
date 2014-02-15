// Analog pin
const int ACCELERATOR = 2;
const int TOUCH       = 3;

// Digital pin
const int DISPLAY1 = 2;
const int DISPLAY2 = 3;
const int HOOK     = 10;
const int BUZZER   = 11;
const int LED      = 13;

// Other
const float VD = 3.256;

boolean is_leaned   = false;
boolean is_hooked   = false;
boolean is_touched1 = false;
boolean is_touched2 = false;
boolean is_touched3 = false;
boolean is_touched4 = false;

void setup() {
  pinMode(HOOK, INPUT);
  digitalWrite(HOOK, HIGH); 
  pinMode(TOUCH, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // 傾いてなければ
  if (!is_leaned) {

    // 加速度センサー
    float z = analogRead(ACCELERATOR) * VD / 1024;
    float zv = z - VD / 2.0;
    float zg = zv / (0.3 * VD / 3.0);

    // 傾いた
    if (zg > 0) {
      is_leaned = true;
    }
  }

  // フックをつけてなければ
  if (!is_hooked && !digitalRead(HOOK)) {

    // 傾いてないのにフックをつけた（減点）
    if (!is_leaned) {
      result -= 10;
    }

    is_hooked = true;
  }

  // タッチしてなければ
  if (!is_touched1 || !is_touched2 || !is_touched3 || !is_touched4) {

    int touchValue = analogRead(TOUCH);

    if (700 <= touchValue && touchValue < 750) {
      if (!is_touched1 && (!is_leaned || !is_hooked)) {
        result -= 10;
      }

      is_touched1 = true;
    }
  }

  delay(500);
}

