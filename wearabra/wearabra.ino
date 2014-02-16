// Analog pin
const int ACCELERATOR = 2;
const int TOUCH       = 4;

// Digital pin
const int DISPLAY1 = 2;
const int DISPLAY2 = 3;
const int HOOK     = 11;
const int BUZZER   = 10;
const int LED      = 13;

const int TOUCH2 = 9;

// Other
const float VD = 3.256;

boolean is_leaned   = false;
boolean is_hooked   = false;
boolean is_touched1 = false;
boolean is_touched2 = false;
boolean is_touched3 = false;
boolean is_touched4 = false;
boolean is_success  = false;

int result = 0;
int time = 0;

// for buzzer
long t1, t2, t3, ta, tb;

const int mB9  = 15804; // シ
const int mG9  = 12543; // ソ
const int mF9  = 11175; // ファ
const int mC9  = 8372;  // ド

const int mA8  = 7040; // ラ
const int mFs8 = 5919; // ファ#
const int mE8  = 5274; // ミ
const int mEf8 = 4978; // ミ♭
const int mD8  = 4698; // レ
const int mC8  = 4186; // ド

const int mB7  = 3951; // シ
const int mBf7 = 3729; // シ♭
const int mA7  = 3520; // ラ
const int mG7  = 3156; // ソ
const int mFs7 = 2960; // ファ#
const int mF7  = 2794; // ファ
const int mEf7 = 2489; // ミ♭
const int mE7  = 2637; // ミ
const int mD7  = 2349; // レ
const int mC7  = 2093; // ド

const int mB6  = 1976; // シ
const int mBf6 = 1865; // シ♭
const int mAf6 = 1661; // ラ♭
const int mG6  = 1568; // ソ
const int mE6  = 1319; // ミ
const int mB5  =  988; // シ
const int mBf5 =  932; // シb

void setup() {
  pinMode(HOOK, INPUT);
  digitalWrite(HOOK, HIGH); 
  pinMode(TOUCH, INPUT);

  pinMode(TOUCH2, INPUT);
  digitalWrite(TOUCH2, HIGH); 

  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  check_leaned();
  check_hooked();

  check_touched_debug();

  check_touched();

  flash_led();

  // タイムアップ
  if (!is_success && 600 == time) {
    soundFailure();
  } 
  // 本番用
  else if (!is_success && is_leaned && is_hooked && is_touched1 && is_touched2 && is_touched3 && is_touched4) {
    soundSuccess();
    soundSuccess();
    is_success = true;
  }
  // デバグ用
//  else if (!is_success && is_leaned && is_hooked) {
//    soundSuccess();
//    soundSuccess();
//    is_success = true;
//  }

  debug();

  delay(100);
  time += 1;
}

/**
 * @param int  buzpin ポート番号
 * @param int  fre    音の周波数
 * @param long timel1 msec
 */
void beep(int fre, long timel1) {
  // the sound producing
  int x;
  long delayHL = (long)(1000000/fre/2);
  long loopn   = (long)((timel1*1000)/(2*delayHL));
  for (x=0;x<loopn;x++) {
    digitalWrite(BUZZER,HIGH);
    digitalWrite(LED, HIGH);  // 点灯
    delayMicroseconds(delayHL);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LED, LOW);  // 消灯
    delayMicroseconds(delayHL);
  }
  delay(5);
}

void check_leaned() {

  // フックをつけてなければ
  if (!is_hooked) {
  
    // 加速度センサー
    float z = analogRead(ACCELERATOR) * VD / 1024;
    float zv = z - VD / 2.0;
    float zg = zv / (0.3 * VD / 3.0);
    
    if ((time % 5) == 0) {
      Serial.print("zg = ");
      Serial.println(zg);
    }
  
    // 傾いた
    if (zg < -0.4) {
      if (!is_leaned)
        result += 10;
      is_leaned = true;
      //digitalWrite(LED, HIGH);  // 点灯
    } 
    else {
      if (is_leaned)
        result -= 10;
      is_leaned = false;
      //digitalWrite(LED, LOW);  // 消灯
    }
  }
}

void check_hooked() {

  // フックをつけてなければ
  if (!is_hooked) {
    if (!digitalRead(HOOK)) {
  
      // 傾いていた
      if (is_leaned) {
        soundCheckPoint();
      }
      
      // フックをつけた（加点）
      result += 10;
      is_hooked = true;
      soundCheckPoint();
    }
  }
}

void check_touched_debug() {

  if (!digitalRead(TOUCH2)) {

    if (!is_touched1) {
      result += 10;
      is_touched1 = true;
      soundCheckPoint();
    }
    else if (!is_touched2) {
      result += 10;
      is_touched2 = true;
      soundCheckPoint();
    }
    else if (!is_touched3) {
      result += 10;
      is_touched3 = true;
      soundCheckPoint();
    }
    else if (!is_touched4) {
      result += 10;
      is_touched4 = true;
      soundCheckPoint();
    }
  }
}

void check_touched() {

  // タッチしてなければ
  if (!is_touched1 || !is_touched2 || !is_touched3 || !is_touched4) {

    int touchValue = analogRead(TOUCH);
    
    if ((time % 5) == 0) {
      Serial.print("touchValue = ");
      Serial.println(touchValue);
    }

    // タッチした（抵抗３個）
    if (230 <= touchValue && touchValue < 280) {

      // タッチした（加点）
      if (!is_touched1) {
        result += 10;
        is_touched1 = true;
        soundCheckPoint();
      }
    }

    // タッチした（抵抗２個）
    else if (530 <= touchValue && touchValue < 550) {

      // タッチした（加点）
      if (!is_touched2) {
        result += 10;
        is_touched2 = true;
        soundCheckPoint();
      }
    }

    // タッチした（抵抗１個）
    else if (680 <= touchValue && touchValue < 720) {

      // タッチした（加点）
      if (!is_touched3) {
        result += 10;
        is_touched3 = true;
        soundCheckPoint();
      }
    }

    // タッチした（抵抗０個）
    else if (950 <= touchValue) {

      // タッチした（加点）
      if (!is_touched4) {
        result += 10;
        is_touched4 = true;
        soundCheckPoint();
      }
    }
  }
}

void flash_led() {
  if (time % 6 * 10 < result)
    digitalWrite(LED, HIGH);  // 点灯
  else
    digitalWrite(LED, LOW);  // 消灯
}

void debug() {

  if ((time % 5) == 0) {
    Serial.print("time: ");
    Serial.print((float)time/10);
    Serial.print(", ");
    Serial.print("leaned: ");
    Serial.print(is_leaned);
    Serial.print(", ");
    Serial.print("hooked: ");
    Serial.print(is_hooked);
    Serial.print(", ");
    Serial.print("touched: ");
    Serial.print(is_touched1);
    Serial.print(is_touched2);
    Serial.print(is_touched3);
    Serial.print(is_touched4);
    Serial.print(", ");
    Serial.print("result: ");
    Serial.println(result);
  }
}

// チェックポイントで鳴らす音楽
void soundCheckPoint() {
  
  if (result == 10) {
    beep(mC7,  100);
    beep(mD7,  100);
  }

  if (result == 20) {
    beep(mEf7, 200);
    beep(mFs7, 100);
    beep(mA7,  100);
  }

  if (result == 30) {
    beep(mC8,  100);
    beep(mE8,  100);
  }
  if (result == 40) {
    beep(mFs8, 100);
    beep(mA8,  100);
  }
  if (result == 50) {
    beep(mC9,  100);
    beep(mF9,  100);
  }
  if (result == 60) {
    beep(mG9,  100);
    beep(mB9,  100);
    delay(500);
  }
}

// 時間内に成功したときに鳴らす音楽
void soundSuccess() {
  beep(mF7, 100);
  beep(mF7, 100);
  beep(mF7, 100);
  beep(mF7, 75);
  delay(125);
  beep(mEf7, 75);
  delay(125);
  beep(mG7, 75);
  delay(125);
  beep(mF7, 300);
  delay(500);
}

// タイムアウトのときに鳴らす音楽
void soundFailure() {
  beep(mB5, 200);
  beep(mB6, 200);
  beep(mBf5, 200);
  beep(mBf6, 200);

  beep(mB5, 200);
  beep(mB6, 200);
  beep(mBf5, 200);
  beep(mBf6, 200);

  beep(mB5, 200);
  beep(mB6, 200);
  beep(mBf5, 200);
  beep(mBf6, 200);

  beep(mB5, 200);
  beep(mB6, 200);
  beep(mBf5, 200);
  beep(mBf6, 200);

  beep(mE6, 500);
  beep(mG6, 100);
  beep(mAf6, 100);
  beep(mBf5, 100);
}

