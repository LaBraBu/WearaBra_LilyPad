/**
 * 定数
 */

// Analog pin
const int ACCELERATOR = 2;

// Digital pin
const int DISPLAY1 = 2;
const int DISPLAY2 = 3;
const int TOUCH    = 9;
const int HOOK     = 10;
const int BUZZER   = 11;
const int LED      = 13;

// Other
const float VD = 3.256;

boolean is_z     = false;
boolean is_hook  = false;
boolean is_touch = false;

int val = 0;

void setup() {
  pinMode(HOOK, INPUT);
  digitalWrite(HOOK, HIGH); 
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // 傾いてなければ
  if (!is_z) {  

    // 加速度センサー
    float z = analogRead(ACCELERATOR) * VD / 1024;
    float zv = z - VD / 2.0;
    float zg = zv / (0.3 * VD / 3.0);

    // 傾けば LED を光らせる
    if (zg > 0) {
      is_z = true;
    }

  // 傾いていれば次のフェーズへ
  } else {

    val = digitalRead(HOOK);
    
    if (val == HIGH) {
      digitalWrite(LED, LOW);
    } else {
      digitalWrite(LED, HIGH);
    }
    
    Serial.println(val);
  }

  delay(300);
}

