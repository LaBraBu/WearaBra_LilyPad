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

int result = 100;
float time = 0;

// for buzzer
long t1, t2, t3, ta, tb;

const int C   = 4186; // ド
const int B   = 3951; // シ
const int Bf  = 3729; // シb
const int A   = 3520; // ラ
const int G   = 3156; // ソ
const int F   = 2794; // ファ
const int Ef  = 2489; // ミb

const int C7  = 2093; // ド
const int B6  = 1976; // シ
const int Bf6 = 1865; // シb
const int Af6 = 1661; // ラb
const int G6  = 1568; // ソ
const int E6  = 1319; // ミ
const int B5  =  988; // シ
const int Bf5 =  932; // シb

void setup() {
  pinMode(HOOK, INPUT);
  digitalWrite(HOOK, HIGH); 
  pinMode(TOUCH, INPUT);

  pinMode(BUZZER, OUTPUT);
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

    // 傾いてないのに、フックをつけた（減点）
    if (!is_leaned) {
      result -= 10;
    }

    is_hooked = true;
  }

  // タッチしてなければ
  if (!is_touched1 || !is_touched2 || !is_touched3 || !is_touched4) {

    int touchValue = analogRead(TOUCH);

    // タッチした（抵抗3個）
    if (230 <= touchValue && touchValue < 280) {

      // 傾いてない or フックをつけてないのに、タッチした（減点）
      if (!is_touched1 && (!is_leaned || !is_hooked)) {
        result -= 10;
      }

      is_touched1 = true;

    // タッチした（抵抗2個）
    } else if (500 <= touchValue && touchValue < 550) {

      // 傾いてない or フックをつけてないのに、タッチした（減点）
      if (!is_touched2 && (!is_leaned || !is_hooked)) {
        result -= 10;
      }

      is_touched2 = true;

    // タッチした（抵抗1個）
    } else if (750 <= touchValue && touchValue < 800) {

      // 傾いてない or フックをつけてないのに、タッチした（減点）
      if (!is_touched3 && (!is_leaned || !is_hooked)) {
        result -= 10;
      }

      is_touched3 = true;

    // タッチした（抵抗0個）
    } else if (1000 <= touchValue) {

      // 傾いてない or フックをつけてないのに、タッチした（減点）
      if (!is_touched4 && (!is_leaned || !is_hooked)) {
        result -= 10;
      }

      is_touched4 = true;
    }
  }

  // タイムアップ
  if (60 < time) {
    soundFailure();

  // 全部終わっていれば、点数を表示
//  } else if (is_leaned && is_hooked && is_touched1 && is_touched2 && is_touched3 && is_touched4) { // 本番用
  } else if (is_leaned && is_hooked) { // デバグ用
    Serial.println(result);
    soundSuccess();
  }

  delay(500);
  time += 0.5;
  Serial.println(time);
}

/**
 * @param int  buzpin ポート番号
 * @param int  fre    音の周波数
 * @param long timel1 msec
 */
void beep(int buzpin, int fre, long timel1) { // the sound producing 
    int x; 
    long delayHL = (long)(1000000/fre/2); 
    long loopn   = (long)((timel1*1000)/(2*delayHL));
    for (x=0;x<loopn;x++) {
        digitalWrite(buzpin,HIGH); 
        delayMicroseconds(delayHL); 
        digitalWrite(buzpin,LOW); 
        delayMicroseconds(delayHL);
    }
    delay(5);
}

void soundSuccess() {
    beep(BUZZER, F, 100);
    beep(BUZZER, F, 100);
    beep(BUZZER, F, 100);
    beep(BUZZER, F, 75);
    delay(125); 
    beep(BUZZER, Ef, 75); 
    delay(125);
    beep(BUZZER, G, 75); 
    delay(125);
    beep(BUZZER, F, 300);
    delay(400);
}

void soundFailure() {
    beep(BUZZER, B5, 200);
    beep(BUZZER, B6, 200);
    beep(BUZZER, Bf5, 200);
    beep(BUZZER, Bf6, 200);

    beep(BUZZER, B5, 200);
    beep(BUZZER, B6, 200);
    beep(BUZZER, Bf5, 200);
    beep(BUZZER, Bf6, 200);

    beep(BUZZER, B5, 200);
    beep(BUZZER, B6, 200);
    beep(BUZZER, Bf5, 200);
    beep(BUZZER, Bf6, 200);

    beep(BUZZER, B5, 200);
    beep(BUZZER, B6, 200);
    beep(BUZZER, Bf5, 200);
    beep(BUZZER, Bf6, 200);

    beep(BUZZER, E6, 500);
    beep(BUZZER, G6, 100);
    beep(BUZZER, Af6, 100);
    beep(BUZZER, Bf5, 100);
}


